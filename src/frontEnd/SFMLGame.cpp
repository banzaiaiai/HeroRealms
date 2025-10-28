#include "frontEnd/SFMLGame.hpp"
#include "backEnd/Joueur.hpp"
#include "backEnd/Partie.hpp"
#include "frontEnd/ZoneCarte.hpp"
#include "frontEnd/Overlay.hpp"
#include <SFML/System/String.hpp>
#include <iostream>
#include <ostream>
#include <string>

SFMLGame::SFMLGame(Partie* partie) 
    : _window(sf::VideoMode(1200, 800), "Jeu de Cartes", sf::Style::Titlebar | sf::Style::Close),
      _partie(partie),
      _carteSelectionnee(nullptr),
      _zoneSource(nullptr),
      _overlay(nullptr){
    
    std::cout << "SFMLGame construit" << std::endl;
    
    _zones.creerZonesStandard();
    
    _overlay._zoneCarte = _zones.getZoneParNom("overlay");
    
    if (_partie) {
        _zones.lierPartie(_partie);
        synchroniserAffichage();
    }
}

SFMLGame::~SFMLGame() {
    std::cout << "SFMLGame détruit" << std::endl;
}

void SFMLGame::setPartie(Partie* partie) {
    _partie = partie;
    if (_partie) {
        _zones.lierPartie(_partie);
        synchroniserAffichage();
    }
}

void SFMLGame::gameLoop() {
    while (_window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void SFMLGame::synchroniserAffichage() {
    if (!_partie) return;
    
    // Nettoyer les cartes graphiques existantes
    _cartesGraphiques.clear();
    
    // Parcourir toutes les zones et créer les cartes graphiques
    for (const auto& zone : _zones.getZones()) {
        for (Carte* carteLogique : zone->getCartesLogiques()) {
            if (_cartesGraphiques.find(carteLogique) == _cartesGraphiques.end()) {
                creerCarteGraphique(carteLogique);
            }
        }
    }
}

void SFMLGame::creerCarteGraphique(Carte* carte) {
    auto carteGraphique = std::make_unique<CarteGraphique>(0, 0, 80, 120, carte);
    _cartesGraphiques[carte] = std::move(carteGraphique);
}

void SFMLGame::processEvents() {
    sf::Event event;
    while (_window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                _window.close();
                break;
                
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    handleMouseClick(event.mouseButton.x, event.mouseButton.y);
                }
                break;
                
            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    handleMouseRelease(event.mouseButton.x, event.mouseButton.y);
                }
                break;
                
            default:
                break;
        }
    }
}

void SFMLGame::handleMouseClick(int mouseX, int mouseY) {
    sf::Vector2f mousePos = _window.mapPixelToCoords(sf::Vector2i(mouseX, mouseY));
    
    // Désélectionner toute carte précédente
    if (_carteSelectionnee) {
        _carteSelectionnee->setSelected(false);
    }
    
    // Chercher la carte graphique cliquée
    for (auto& [carteLogique, carteGraphique] : _cartesGraphiques) {
        if (carteGraphique->contains(mousePos)) {
            _carteSelectionnee = carteGraphique.get();
            _positionOriginale = carteGraphique->getPosition();
            std::cout<<carteGraphique->getCarteLogique()->getName()<<std::endl;
            // Trouver la zone source
            for (const auto& zone : _zones.getZones()) {
                if (zone->contient(_positionOriginale)) {
                    _zoneSource = zone.get();
                    std::cout<<_zoneSource->getNom()<<std::endl;
                    break;
                }
            }
            
            _carteSelectionnee->setSelected(true);
            break;
        }
    }
}

void SFMLGame::handleMouseRelease(int mouseX, int mouseY) {
    if (!_carteSelectionnee || !_zoneSource) return;
    
    sf::Vector2f mousePos = _window.mapPixelToCoords(sf::Vector2i(mouseX, mouseY));
    ZoneCarte* zoneCible = _zones.getZoneContenant(mousePos);
    
    Carte* carteLogique = _carteSelectionnee->getCarteLogique();
    
    if (zoneCible && carteLogique) {
        if (deplacementValide(_zoneSource, zoneCible, carteLogique)) {
            std::cout<<"deplacement possible"<<std::endl;
            appliquerDeplacementLogique(carteLogique, _zoneSource, zoneCible);
            
            // L'affichage sera mis à jour via synchroniserAffichage()
        } else {
            // Annuler visuellement
            _carteSelectionnee->setPosition(_positionOriginale.x,_positionOriginale.y);
        }
    } else {
        // Retour à la position originale
        _carteSelectionnee->setPosition(_positionOriginale.x,_positionOriginale.y);
    }
    
    _carteSelectionnee->setSelected(false);
    _carteSelectionnee = nullptr;
    _zoneSource = nullptr;
}

void SFMLGame::update() {
    // Synchroniser l'affichage avec l'état logique
    if (_partie) {
        _zones.mettreAJourZones(_partie);
        synchroniserAffichage();
    }
    
    // Mettre à jour les positions des cartes graphiques
    for (const auto& zone : _zones.getZones()) {
        auto positions = zone->calculerPositionsCartes();
        const auto& cartes = zone->getCartesLogiques();
        
        for (size_t i = 0; i < cartes.size() && i < positions.size(); i++) {
            auto it = _cartesGraphiques.find(cartes[i]);
            if (it != _cartesGraphiques.end()) {
                it->second->setPosition(positions[i].x, positions[i].y);
            }
        }
    }
}

void SFMLGame::render() {
    _window.clear(sf::Color(0, 100, 0)); // Fond vert
    
    // Dessiner les zones
    _zones.dessinerZones(_window);


    
    // Dessiner les cartes graphiques
    for (auto& [carteLogique, carteGraphique] : _cartesGraphiques) {
        carteGraphique->draw(_window);
    }

    if (_overlay.getIsOverlay()) {
        _window.draw(_overlay._background);
        _overlay._zoneCarte->dessiner(_window);
    }
    
    _window.display();
}

bool SFMLGame::deplacementValide(ZoneCarte* source, ZoneCarte* cible, Carte* carte) {
    if (!source || !cible || !carte || !_partie) return false;
    
    // Règles de déplacement basées sur les noms des zones
    std::string sourceNom = source->getNom();
    std::string cibleNom = cible->getNom();
    // Exemple de règles
    if (/*sourceNom == "main_joueur" && cibleNom == "plateau"*/ true) {
        //return _partie->getJoueurActuelle()->getOr() >= carte->getCoupOr();
        return true;
        
    }
    
    if (/*sourceNom == "marche" && cibleNom == "main_joueur"*/ true) {
        // return _partie->getJoueurActuelle()->getOr() >= carte->getCoupOr();
        return true;
    }
    
    return false;
}

void SFMLGame::appliquerDeplacementLogique(Carte* carte, ZoneCarte* source, ZoneCarte* cible) {
    if (!carte || !source || !cible || !_partie) return;
    
    // Ici tu appelles les méthodes de ta logique métier
    // Exemple: _partie->deplacerCarte(carte, source->getNom(), cible->getNom());
    
    // Pour l'instant, on met à jour juste les zones graphiques
    std::string tmpSource=source->getNom().substr(0,source->getNom().size()-1);
    std::string tmpCible=cible->getNom().substr(0,cible->getNom().size()-1);
    std::cout<<tmpSource<<" "<< tmpCible<<std::endl;
    if(tmpSource=="main_joueur" && tmpCible=="plateau_joueur"){
        std::cout<<"réussi 1"<<std::endl;
        Joueur *joueur= _partie->getJoueurActuelle();
        joueur->mouve(carte,joueur->getMain(),joueur->getPlateau());
    }
    if(tmpSource=="marche" && tmpCible=="main_joueur"){
        std::cout<<"réussi 2"<<std::endl;
        Joueur *joueur= _partie->getJoueurActuelle();
        joueur->mouve(carte,_partie->getRiviere(),joueur->getMain());
    }
}
