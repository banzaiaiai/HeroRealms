#include "frontEnd/SFMLGame.hpp"
#include "backEnd/Joueur.hpp"
#include "backEnd/Partie.hpp"
#include "frontEnd/ZoneCarte.hpp"
#include <SFML/Graphics/Font.hpp>
#include <iostream>
#include <set>

SFMLGame::SFMLGame(Partie* partie) 
    : _window(sf::VideoMode(1200, 800), "Jeu de Cartes", sf::Style::Titlebar | sf::Style::Close),
      _partie(partie),
      _carteSelectionnee(nullptr),
      _carteSelectionneeId(-1),
      _zoneSource(nullptr),
      _buttonAtacker("attaque", sf::Vector2f(40, 650), sf::Vector2f(100, 100)),
      _buttonFinTour("fin de tour", sf::Vector2f(920, 370), sf::Vector2f(200, 50))
{
    std::cout << "SFMLGame construit" << std::endl;
    
    _zones.creerZonesStandard();
    
    if (_partie) {
        _zones.lierPartie(_partie);
        synchroniserAffichage();
    }

    _overlay = Overlay();
    _isOverlay = false;
    _font.loadFromFile("arial.ttf");
    if (!_font.loadFromFile("arial.ttf")) {
        std::cerr << "Erreur lors du chargement de la police" << std::endl;
    }
    rendertext();
}

SFMLGame::~SFMLGame() {
    std::cout << "SFMLGame détruit" << std::endl;
}

void SFMLGame::rendertext() {
    _textJoueur1.setFont(_font);
    _textJoueur1.setCharacterSize(24);
    _textJoueur1.setFillColor(sf::Color::Red);
    _textJoueur1.setPosition(10.f, 10.f);

    _textJoueur2.setFont(_font);
    _textJoueur2.setCharacterSize(24);
    _textJoueur2.setFillColor(sf::Color::Red);
    _textJoueur2.setPosition(10.f, 40.f);
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
    
    // Nettoyer les cartes graphiques obsolètes
    // Garder seulement celles qui existent encore dans la partie
    std::set<int> idsExistants;
    
    // Parcourir toutes les zones et collecter les IDs des cartes observées
    for (const auto& zone : _zones.getZones()) {
        for (const Carte* carte : zone->getCartesObservees()) {
            idsExistants.insert(carte->getId());
            
            // Créer la carte graphique si elle n'existe pas
            if (_cartesGraphiques.find(carte->getId()) == _cartesGraphiques.end()) {
                creerCarteGraphique(carte);
            }
        }
    }
    
    // Supprimer les cartes graphiques qui n'existent plus
    for (auto it = _cartesGraphiques.begin(); it != _cartesGraphiques.end();) {
        if (idsExistants.find(it->first) == idsExistants.end()) {
            it = _cartesGraphiques.erase(it);
        } else {
            ++it;
        }
    }
}

void SFMLGame::creerCarteGraphique( const Carte* carte) {
    if (!carte) return;
    
    auto carteGraphique = std::make_unique<CarteGraphique>(0, 0, 80, 120, carte);
    _cartesGraphiques[carte->getId()] = std::move(carteGraphique);
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
        // Je pense pas utile
        // _carteSelectionnee = nullptr;
        _carteSelectionneeId = -1;
    }
    
    // Chercher la carte graphique cliquée (par ID)
    for (auto& [carteId, carteGraphique] : _cartesGraphiques) {
        if (carteGraphique->contains(mousePos)) {
            _carteSelectionnee = carteGraphique.get();
            _carteSelectionneeId = carteId;
            _positionOriginale = carteGraphique->getPosition();
            
            std::cout << "Carte cliquée: ID=" << carteId 
                      << ", Nom=" << carteGraphique->getCarteLogique()->getName() << std::endl;
            
            // Trouver la zone source
            for (const auto& zone : _zones.getZones()) {
                if (zone->contient(_positionOriginale)) {
                    _zoneSource = zone.get();
                    std::cout << "Zone source: " << _zoneSource->getNom() << std::endl;
                    break;
                }
            }
            
            _carteSelectionnee->setSelected(true);
            break;
        }
    }
}

void SFMLGame::handleMouseRelease(int mouseX, int mouseY) {
    if (!_carteSelectionnee || !_zoneSource || _carteSelectionneeId == -1) return;
    
    sf::Vector2f mousePos = _window.mapPixelToCoords(sf::Vector2i(mouseX, mouseY));
    ZoneCarte* zoneCible = _zones.getZoneContenant(mousePos);
    
    if (zoneCible) {
        if (deplacementValide(_zoneSource, zoneCible, _carteSelectionneeId)) {
            std::cout << "Déplacement valide" << std::endl;
            appliquerDeplacementLogique(_carteSelectionneeId, _zoneSource, zoneCible);
        } else {
            std::cout << "Déplacement invalide" << std::endl;
            // Annuler visuellement
            _carteSelectionnee->setPosition(_positionOriginale.x, _positionOriginale.y);
        }
    } else {
        // Retour à la position originale
        _carteSelectionnee->setPosition(_positionOriginale.x, _positionOriginale.y);
    }
    
    _carteSelectionnee->setSelected(false);
    // Je pense pas utile
    // _carteSelectionnee = nullptr;
    _carteSelectionneeId = -1;
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
        const auto& cartesObservees = zone->getCartesObservees();
        
        for (size_t i = 0; i < cartesObservees.size() && i < positions.size(); i++) {
            int carteId = cartesObservees[i]->getId();
            auto it = _cartesGraphiques.find(carteId);
            if (it != _cartesGraphiques.end()) {
                it->second->setPosition(positions[i].x, positions[i].y);
            }
        }
    }
    
    // Mise à jour des textes
    if (_partie && _partie->getJoueurActuelle()) {
        _textJoueur1.setString("Joueur 1 - Or: " + 
            std::to_string(_partie->getJoueurActuelle()->getOr()) + 
            " Vie: " + std::to_string(_partie->getJoueurActuelle()->getPv()));
        _textJoueur2.setString("Joueur 2 - Or: " + 
            std::to_string(_partie->getJoueurActuelle()->getOr()) + 
            " Vie: " + std::to_string(_partie->getJoueurActuelle()->getPv()));
    }
    
    _buttonAtacker.update(_window);
    _buttonFinTour.update(_window);
}

void SFMLGame::render() {
    _window.clear(sf::Color(0, 100, 0));
    
    // Dessiner les zones
    _zones.dessinerZones(_window);
    
    // Dessiner les cartes graphiques
    for (auto& [carteId, carteGraphique] : _cartesGraphiques) {
        carteGraphique->draw(_window);
    }

    if (_isOverlay) {
        _window.draw(_overlay._background);
        _overlay._zoneCarte.dessiner(_window);
    }

    _window.draw(_textJoueur1);
    _window.draw(_textJoueur2);

    _buttonAtacker.draw(_window);
    _buttonFinTour.draw(_window);

    _window.display();
}

bool SFMLGame::deplacementValide(ZoneCarte* source, ZoneCarte* cible, int carteId) {
    if (!source || !cible || carteId == -1 || !_partie) return false;
    
    std::string sourceNom = source->getNom();
    std::string cibleNom = cible->getNom();
    
    // Extraire le type de zone et le joueur
    auto extraireInfo = [](const std::string& nom) -> std::pair<std::string, int> {
        size_t pos = nom.find_last_of("_");
        if (pos != std::string::npos && pos + 1 < nom.size()) {
            std::string type = nom.substr(0, pos);
            int joueur = std::stoi(nom.substr(pos + 1)) - 1;
            return {type, joueur};
        }
        return {nom, -1};
    };
    
    auto [typeSource, joueurSource] = extraireInfo(sourceNom);
    auto [typeCible, joueurCible] = extraireInfo(cibleNom);
    
    int joueurActuel = _partie->getJoueurActuelle()->getId();
    
    // RÈGLE 1: Main → Plateau (même joueur)
    if (typeSource == "main_joueur" && typeCible == "plateau_joueur" && 
        joueurSource == joueurActuel && joueurCible == joueurActuel) {
        // Vérifier le coût en or
        const Carte* carte = _partie->getJoueurActuelle()->getCarteById(carteId);
        if (carte) {
            return _partie->getJoueurActuelle()->getOr() >= carte->getCoupOr();
        }
        return false;
    }
    
    // RÈGLE 2: Marché → Main ou Défausse
    if (sourceNom == "marche" && 
        (typeCible == "main_joueur" || typeCible == "defausse_joueur") &&
        joueurCible == joueurActuel) {
        return true;
    }
    
    // RÈGLE 3: Plateau → Défausse (pour défausser une carte jouée)
    if (typeSource == "plateau_joueur" && typeCible == "defausse_joueur" &&
        joueurSource == joueurActuel && joueurCible == joueurActuel) {
        return true;
    }
    
    return false;
}

void SFMLGame::appliquerDeplacementLogique(int carteId, ZoneCarte* source, ZoneCarte* cible) {
    if (carteId == -1 || !source || !cible || !_partie) return;
    
    std::string sourceNom = source->getNom();
    std::string cibleNom = cible->getNom();
    
    Joueur* joueur = _partie->getJoueurActuelle();
    if (!joueur) return;
    
    std::cout << "Déplacement: " << sourceNom << " -> " << cibleNom 
              << " (Carte ID: " << carteId << ")" << std::endl;
    
    // CASE 1: Main → Plateau
    if (sourceNom.find("main_joueur") != std::string::npos && 
        cibleNom.find("plateau_joueur") != std::string::npos) {
        
        if (joueur->jouerCarte(carteId)) {
            std::cout << "Carte jouée avec succès" << std::endl;
        } else {
            std::cerr << "Échec de jouer la carte" << std::endl;
        }
    }
    // CASE 2: Marché → Main
    else if (sourceNom == "marche" && cibleNom.find("main_joueur") != std::string::npos) {
        // Récupérer la carte depuis la rivière (Partie)
        auto carte = _partie->retirerCarteRiviere(carteId);
        if (carte) {
            joueur->ajouterCarte(std::move(carte), ZoneType::Main);
            std::cout << "Carte achetée depuis le marché" << std::endl;
        }
    }
    // CASE 3: Marché → Défausse
    else if (sourceNom == "marche" && cibleNom.find("defausse_joueur") != std::string::npos) {
        auto carte = _partie->retirerCarteRiviere(carteId);
        if (carte) {
            joueur->ajouterCarte(std::move(carte), ZoneType::Defausse);
            std::cout << "Carte défaussée depuis le marché" << std::endl;
        }
    }
    // CASE 4: Plateau → Défausse
    else if (sourceNom.find("plateau_joueur") != std::string::npos && 
             cibleNom.find("defausse_joueur") != std::string::npos) {
        joueur->defausserCarte(carteId, ZoneType::Plateau);
        std::cout << "Carte défaussée depuis le plateau" << std::endl;
    }
}