#include "frontEnd/SFMLGame.hpp"
#include "backEnd/Joueur.hpp"
#include "backEnd/Partie.hpp"
#include "frontEnd/ZoneCarte.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include <set>
#include <string>



SFMLGame::SFMLGame(Partie* partie) 
    : _window(sf::VideoMode(1200, 800), "Jeu de Cartes", sf::Style::Titlebar | sf::Style::Close),
    _partie(partie),
    _carteSelectionnee(nullptr),
    _carteSelectionneeId(-1),
    _zoneSource(nullptr),

    // UI elements
    _overlay(),
    _buttonAtacker("attaque", sf::Vector2f(40, 345), sf::Vector2f(100, 100)),
    _buttonFinTour("fin de tour", sf::Vector2f(155, 370), sf::Vector2f(200, 50)),
    _buttonDefausse1("defausse1", sf::Vector2f(960, 640), sf::Vector2f(80, 120)),
    _buttonDefausse2("defausse2", sf::Vector2f(960, 20), sf::Vector2f(80, 120)),
    _buttonpioche1("pioche1", sf::Vector2f(1060, 640), sf::Vector2f(80, 120)),
    _buttonpioche2("pioche2", sf::Vector2f(1060, 20), sf::Vector2f(80, 120)),
    _buttondeffausse("deffausse", sf::Vector2f(1060, 335), sf::Vector2f(80, 120)),

    _rectangeHaut(sf::Vector2f(140.f, 160.f)),
    _rectangeBas(sf::Vector2f(140.f, 160.f)),

    _backCarteHaut(sf::Vector2f(80.f, 120.f)),
    _backCarteBas(sf::Vector2f(80.f, 120.f))
{
    std::cout << "SFMLGame construit" << std::endl;
    
    _zones.creerZonesStandard();
    
    partie->setOverlay(&_overlay);
    
    if (_partie) {
        _zones.lierPartie(_partie);
        synchroniserAffichage();
    }

    _font.loadFromFile("arial.ttf");
    if (!_font.loadFromFile("arial.ttf")) {
        std::cerr << "Erreur lors du chargement de la police" << std::endl;
    }
    rendertext();

    // Configurer les rectangles
    _rectangeHaut.setPosition(5.f, 5.f);
    _rectangeHaut.setFillColor(sf::Color::Black);

    _rectangeBas.setPosition(5.f, 640.f);
    _rectangeBas.setFillColor(sf::Color::Black);

    // Load the texture into a member so it stays valid for the lifetime
    // of the SFMLGame (RectangleShape stores a pointer to the texture).
    if (!_backCarteTexture.loadFromFile("assets/carte/hero_realms_back.jpg")) {
        std::cerr << "Erreur: impossible de charger assets/carte/hero_realms_back.jpg" << std::endl;
    }

    _backCarteHaut.setTexture(&_backCarteTexture);
    _backCarteHaut.setPosition(1060.f, 640.f);

    _backCarteBas.setTexture(&_backCarteTexture);
    _backCarteBas.setPosition(1060.f, 20.f);


}

SFMLGame::~SFMLGame() {
    std::cout << "SFMLGame détruit" << std::endl;
}

void SFMLGame::rendertext() {
    _textJoueur1.setFont(_font);
    _textJoueur1.setCharacterSize(24);
    _textJoueur1.setFillColor(sf::Color::Red);
    _textJoueur1.setPosition(20.f, 640.f);

    _textJoueur2.setFont(_font);
    _textJoueur2.setCharacterSize(24);
    _textJoueur2.setFillColor(sf::Color::Red);
    _textJoueur2.setPosition(20.f, 5.f);
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
                if(_buttonFinTour.isMouseOver(_window) and event.mouseButton.button == sf::Mouse::Left) {
                    std::cout << "Fin du tour cliquée" << std::endl;
                    finDeTour();
                }
                if(_buttonAtacker.isMouseOver(_window) and event.mouseButton.button == sf::Mouse::Left) {
                    std::cout << "Attaque cliquée" << std::endl;
                    if(_partie->getJoueurActuelle()->getDegat()>0 && _partie->getAutreJoueurActuelle()->getPlateau().size()>=0){
                        const Carte jouerCible = Carte("Joueur",0,Faction::Neutre,"assets/alternative_carte/none.jpg");
                        std::vector<const Carte*> cible;
                        cible.push_back(&jouerCible);
                        int id=jouerCible.getId();
                        auto idCarteSelect=_overlay.openOverlay("test",_partie->getAutreJoueurActuelle()->getPlateau(),cible);
                        std::cout<<"idCarteSelect="<<idCarteSelect<<"id joueur"<<id<<std::endl;
                        if(id==idCarteSelect and !_partie->getAutreJoueurActuelle()->possedeGardien()) {   
                            std::cout<<"attaque au joueur"<<std::endl;
                            _partie->getAutreJoueurActuelle()->recevoirDegat(_partie->getJoueurActuelle()->getDegat());
                            _partie->getJoueurActuelle()->setDegat(0); // Réinitialiser les dégâts après l'attaque
                            // regarde la victoire
                            if(_partie->getAutreJoueurActuelle()->getPv()<=0){
                                std::cout<<"Le joueur "<<_partie->getJoueurActuelle()->getNom()<<" a gagné la partie!"<<std::endl;
                                _window.close();
                            }
                        }
                        else if(_partie->attaque(idCarteSelect)){
                            std::cout<<"carte selectionné id="<<idCarteSelect<<std::endl;
                        }
                        
                    }
                    else {
                        std::cout<<"vous n'avez pas de dégât pour attaquer"<<std::endl;
                    } 
                }
                else if (_buttonDefausse1.isMouseOver(_window) and event.mouseButton.button == sf::Mouse::Left) {
                    std::cout << "Defausse1 cliquée" << std::endl;
                    _overlay.openOverlay("defausse",_partie->getJoueurParId(0)->getDefausse());
                }
                else if (_buttonDefausse2.isMouseOver(_window) and event.mouseButton.button == sf::Mouse::Left) {
                    std::cout << "Defausse2 cliquée" << std::endl;
                    _overlay.openOverlay("defausse",_partie->getJoueurParId(1)->getDefausse());
                }
                else if (_buttonpioche1.isMouseOver(_window) and event.mouseButton.button == sf::Mouse::Left) {
                    std::cout << "Pioche1 cliquée" << std::endl;
                    _overlay.openOverlay("pioche",_partie->getJoueurParId(0)->getPioche());
                    if (_partie->getAutreJoueurParId(0)) {
                        _partie->getAutreJoueurParId(0)->melangerPioche();
                    }
                }
                else if (_buttonpioche2.isMouseOver(_window) and event.mouseButton.button == sf::Mouse::Left) {
                    std::cout << "Pioche2 cliquée" << std::endl;
                    _overlay.openOverlay("pioche",_partie->getJoueurParId(1)->getPioche());
                    // Shuffle the actual player's internal pioche instead of passing a temporary
                    if (_partie->getAutreJoueurParId(1)) {
                        _partie->getAutreJoueurParId(1)->melangerPioche();
                    }
                }
                else if (_buttondeffausse.isMouseOver(_window) and event.mouseButton.button == sf::Mouse::Left) {
                    std::cout << "Defausse generale cliquée" << std::endl;
                    _overlay.openOverlay("defausse general",_partie->getDefausseCommune());
                }

                else if (event.mouseButton.button == sf::Mouse::Left) {
                    handleMouseClick(event.mouseButton.x, event.mouseButton.y);
                }
                else if (event.mouseButton.button == sf::Mouse::Right) {
                    sf::Vector2f mousePos = _window.mapPixelToCoords(
                        sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

                    for (auto& [carteId, carteGraphique] : _cartesGraphiques) {
                        if (carteGraphique->contains(mousePos)) {
                            // Crée une version agrandie de la carte
                            const Carte* carte = carteGraphique->getCarteLogique();
                            _carteAgrandi = std::make_unique<CarteGraphique>(
                                430.f, 180.f, 320.f, 450.f, carte);
                            break;
                        }
                    }
                }
                break;
                
            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    handleMouseRelease(event.mouseButton.x, event.mouseButton.y);
                }
                else if (event.mouseButton.button == sf::Mouse::Right) {
                    _carteAgrandi.reset();
                }

                break;
                
            default:
                break;
        }
    }
}
void SFMLGame::finDeTour() {
    _partie->getJoueurActuelle()->resetAll();
    _partie->resetetatFaction();
    _partie->getJoueurActuelle()->defausserCarte();
    _partie->passerAuJoueurSuivant();
}

void SFMLGame::handleMouseClick(int mouseX, int mouseY) {
    sf::Vector2f mousePos = _window.mapPixelToCoords(sf::Vector2i(mouseX, mouseY));
    
    // Désélectionner toute carte précédente
    if (_carteSelectionnee) {
        _carteSelectionnee->setSelected(false);
        // Je pense pas utile
        _carteSelectionnee = nullptr;
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

                    // ajout de la logique pour engager une carte
                    if(_zoneSource){
                        std::string name=_zoneSource->getNom().substr(0,_zoneSource->getNom().size()-1);   
                        if(name=="plateau_joueur"){
                            std::cout<<"réussi"<<std::endl;
                            Joueur* joueur=_partie->getJoueurActuelle();
                            if(!joueur->engagerCarte(_carteSelectionneeId)){
                                std::cout<<"erreur ppour engager la carte"<<std::endl;
                            }
                        }
                    }
                    break;
                }
            }
            
            _carteSelectionnee->setSelected(true);
            break;
        }
    }
}

void SFMLGame::handleMouseRelease(int mouseX, int mouseY) {
    if (!_carteSelectionnee || !_zoneSource || _carteSelectionneeId == -1) 
        return;
    
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
    _carteSelectionnee = nullptr;
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
        _textJoueur1.setString("J1 :\nOr: "+std::to_string(_partie->getJoueurActuelle()->getOr()) + "\n"+
            "Vie: " + std::to_string(_partie->getJoueurActuelle()->getPv())+"\n"+
            "Degat: " + std::to_string(_partie->getJoueurActuelle()->getDegat()));
        _textJoueur2.setString("J2 :\nOr: "+std::to_string(_partie->getAutreJoueurActuelle()->getOr()) + "\n"+
            "Vie: " + std::to_string(_partie->getAutreJoueurActuelle()->getPv())+ "\n"+
            "Degat: " + std::to_string(_partie->getAutreJoueurActuelle()->getDegat()));
    }
    
    _buttonAtacker.update(_window);
    _buttonFinTour.update(_window);
    _buttonDefausse1.update(_window);
    _buttonDefausse2.update(_window);
    _buttonpioche1.update(_window);
    _buttonpioche2.update(_window);
    _buttondeffausse.update(_window);
}

void SFMLGame::render() {
    _window.clear(sf::Color(0, 100, 0));
    
    // Dessiner les zones
    _zones.dessinerZones(_window);

    _buttonDefausse1.draw(_window);
    _buttonDefausse2.draw(_window); 
    _buttonpioche1.draw(_window);
    _buttonpioche2.draw(_window);
    _buttondeffausse.draw(_window);

    // Dessiner les cartes graphiques
    for (auto& [carteId, carteGraphique] : _cartesGraphiques) {
        carteGraphique->updateAppearance();
        carteGraphique->draw(_window);
    }


    _window.draw(_rectangeHaut);
    _window.draw(_rectangeBas);

    _window.draw(_textJoueur1);
    _window.draw(_textJoueur2);

    _buttonAtacker.draw(_window);
    _buttonFinTour.draw(_window);

    _window.draw(_backCarteHaut);
    _window.draw(_backCarteBas);

    if (_carteAgrandi) {
        _carteAgrandi->draw(_window);
    }

    _window.display();
}

/**
    To DO :
    Corriger le deplacementValide pour qu'il prenne en compte les règles du jeu.
**/
bool SFMLGame::deplacementValide(ZoneCarte* source, ZoneCarte* cible, int carteId) {
    if (!source || !cible || carteId == -1 || !_partie) 
        return false;
    
    std::string sourceNom = source->getNom();
    std::string cibleNom = cible->getNom();
    
    Joueur* joueur = _partie->getJoueurActuelle();
    
    std::cout << " Tente le deplacement Déplacement: " << sourceNom << " -> " << cibleNom 
              << " (Carte ID: " << carteId << ")" << std::endl;
    if (!joueur) return false;
    // RÈGLE 1: Marché → Main ou Défausse
    cibleNom = cibleNom.substr(0,cibleNom.size()-1); // enlever le _X à la fin
    // On va chercher la carte dans le vecteur de cartes du marcher
    // Pour en extraire le coup en or
    // Normalement ce n'est que de la lecture pas de probléme
    int coupOr=0;
    auto cartes = source->_cartesObservees;
        for (auto carte : cartes){
        coupOr=carte->getCoupOr();
    }
    
    if ((sourceNom == "marche" &&
        (cibleNom == "main_joueur" || cibleNom == "defausse_joueur")) ||
        (sourceNom == "fire gem" && 
        (cibleNom == "main_joueur" || cibleNom == "defausse_joueur"))) {
        
        if(coupOr==-1){
            std::cout<<"Probléme d'achat"<<std::endl;
            return false;
        }
        if (coupOr && (joueur->getOr() >= coupOr)){
            joueur->setOr(joueur->getOr() - coupOr);
            std::cout << "Or suffisant pour acheter la carte" << std::endl;
            return true;
        }
        else {
            std::cout << "Or insuffisant pour acheter la carte" << std::endl;
            std::cout<< "Cout de la carte: " << coupOr << ", Or du joueur: " << joueur->getOr() << std::endl;
            return false;
        }
    }   
    return true;
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
            joueur->ajouterCarte(std::move(carte), ZoneType::Defausse);
            std::cout << "Carte achetée depuis le marché" << std::endl;
        }
    }
    // CASE 2b: Fire gem → Main
    else if (sourceNom == "fire gem" && cibleNom.find("main_joueur") != std::string::npos) {
        auto carte = _partie->retirerGemmeFeu(carteId);
        if (carte) {
            joueur->ajouterCarte(std::move(carte), ZoneType::Defausse);
            std::cout << "Carte achetée depuis la gemme feu" << std::endl;
        }
    }
    // CASE 3: Marché → Défausse
    else if (sourceNom == "marche" && cibleNom.find("defausse_joueur") != std::string::npos) {
        auto carte = _partie->retirerCarteRiviere(carteId);
        if (carte) {
            joueur->ajouterCarte(std::move(carte), ZoneType::Defausse);
            std::cout << "Carte acheter depuis le marché" << std::endl;
            
        }
    }
    // CASE 3b: Fire gem → Défausse
    else if (sourceNom == "fire gem" && cibleNom.find("defausse_joueur") != std::string::npos) {
        auto carte = _partie->retirerGemmeFeu(carteId);
        if (carte) {
            joueur->ajouterCarte(std::move(carte), ZoneType::Defausse);
            std::cout << "Carte achetée depuis la gemme feu" << std::endl;
        }
    }
    // CASE 4: Plateau → Défausse
    else if (sourceNom.find("plateau_joueur") != std::string::npos && 
             cibleNom.find("defausse_joueur") != std::string::npos) {
        joueur->defausserCarte(carteId, ZoneType::Plateau);
        std::cout << "Carte défaussée depuis le plateau" << std::endl;
    }
}
