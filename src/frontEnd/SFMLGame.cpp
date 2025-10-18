#include "frontEnd/SFMLGame.hpp"
#include <iostream>

// Définition des variables globales (si elles existent ailleurs)
extern std::vector<Carte>* GLOBALRiviere;
extern Joueur* GLOBALJoueurActif;
extern Joueur* GLOBALJoueurCible;
extern Carte* GLOBALCarteActif;


#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

SFMLGame::SFMLGame() 
    : _window(sf::VideoMode(800, 600), "Jeu de Cartes", sf::Style::Titlebar | sf::Style::Close),
      _carteSelectionnee(nullptr), 
      _zoneSource(nullptr),
      _positionOriginale(0, 0) {
    
    std::cout << "SFMLGame construit " << this << std::endl;
    
    // Initialiser les composants
    initialiserZones();
    initialiserCartes();
}

SFMLGame::~SFMLGame() {
    std::cout << "SFMLGame détruit " << this << std::endl;
}

void SFMLGame::gameLoop() {
    while (_window.isOpen()) {
        processEvents();
        update();
        render();
    }
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
                
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape) {
                    _window.close();
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
    
    // Vérifier si on clique sur une carte graphique
    for (auto& carte : _cartesGraphiques) {
        if (carte.contains(mousePos)) {
            _carteSelectionnee = &carte;
            _positionOriginale = carte.getPosition();
            _zoneSource = _zones.getZoneContenant(_positionOriginale);
            carte.setSelected(true);
            std::cout << "Carte sélectionnée: " << carte.getCarteLogique()->getName() << std::endl;
            break;
        }
    }
}

void SFMLGame::handleMouseRelease(int mouseX, int mouseY) {
    if (!_carteSelectionnee) return;
    
    sf::Vector2f mousePos = _window.mapPixelToCoords(sf::Vector2i(mouseX, mouseY));
    ZoneCarte* zoneCible = _zones.getZoneContenant(mousePos);
    
    // Récupérer la carte logique associée
    Carte* carteLogique = _carteSelectionnee->getCarteLogique();
    
    if (zoneCible && _zoneSource && carteLogique) {
        // Vérifier si le déplacement est valide LOGIQUEMENT
        if (deplacementValide(_zoneSource->getNom(), zoneCible->getNom(), carteLogique)) {
            // Appliquer la logique métier
            appliquerDeplacementLogique(carteLogique, zoneCible->getNom());
            
            // Mettre à jour la position graphique
            deplacerCarteGraphique(_carteSelectionnee, zoneCible);
            
            std::cout << "Carte déplacée de " << _zoneSource->getNom() 
                      << " vers " << zoneCible->getNom() << std::endl;
        } else {
            // Annuler le déplacement graphique - retour à la position originale
            _carteSelectionnee->setPosition(_positionOriginale.x,_positionOriginale.y);
            std::cout << "Déplacement invalide!" << std::endl;
        }
    } else {
        // Si pas de zone cible valide, retour à l'original
        _carteSelectionnee->setPosition(_positionOriginale.x,_positionOriginale.y);
    }
    
    // Désélectionner
    _carteSelectionnee->setSelected(false);
    _carteSelectionnee = nullptr;
    _zoneSource = nullptr;
}

void SFMLGame::update() {
    // Mettre à jour la logique du jeu si nécessaire
    // Exemple: animations, timers, etc.
}

void SFMLGame::render() {
    _window.clear(sf::Color(0, 100, 0)); // Fond vert style table de jeu
    
    // Dessiner les zones en premier (en arrière-plan)
    _zones.dessinerZones(_window);
    
    // Dessiner les cartes graphiques
    for (const auto& carte : _cartesGraphiques) {
        carte.draw(_window);
    }
    
    _window.display();
}

bool SFMLGame::deplacementValide(const std::string& source, const std::string& cible, Carte* carte) {
    // Règles de déplacement basées sur la logique métier
    
    // De la main vers le plateau
    if (source == "main_joueur" && cible == "plateau") {
        return GLOBALJoueurActif && GLOBALJoueurActif->getOr() >= carte->getCoupOr();
    }
    
    // Du plateau vers la défausse
    if (source == "plateau" && cible == "defausse") {
        return true; // Toujours autorisé
    }
    
    // De la pioche vers la main
    if (source == "pioche" && cible == "main_joueur") {
        return true; // Piocher est toujours autorisé
    }
    
    // Du marché vers la main (achat)
    if (source == "marche" && cible == "main_joueur") {
        return GLOBALJoueurActif && GLOBALJoueurActif->getOr() >= carte->getCoupOr();
    }
    
    return false;
}

void SFMLGame::appliquerDeplacementLogique(Carte* carte, const std::string& zoneCible) {
    if (!carte || !GLOBALJoueurActif) return;
    
    if (zoneCible == "plateau") {
        // Jouer une carte depuis la main
        GLOBALJoueurActif->setOr(GLOBALJoueurActif->getOr() - carte->getCoupOr());
        // TODO: Déclencher les effets OnPlay
        // carte->trigger(OnPlay, context);
        
    } else if (zoneCible == "defausse") {
        // Défausser une carte
        // TODO: Gérer la défausse dans la logique métier
        
    } else if (zoneCible == "main_joueur") {
        // Piocher ou acheter une carte
        if (_zoneSource && _zoneSource->getNom() == "pioche") {
            // TODO: Gérer la pioche dans la logique métier
        } else if (_zoneSource && _zoneSource->getNom() == "marche") {
            // Achat depuis le marché
            GLOBALJoueurActif->setOr(GLOBALJoueurActif->getOr() - carte->getCoupOr());
            // TODO: Retirer la carte du marché
        }
    }
}

void SFMLGame::deplacerCarteGraphique(CarteGraphique* carte, ZoneCarte* zone) {
    if (!carte || !zone) return;
    
    // Positionner la carte au centre de la zone
    float x = zone->getBounds().left + (zone->getBounds().width - carte->getSize().x) / 2;
    float y = zone->getBounds().top + (zone->getBounds().height - carte->getSize().y) / 2;
    carte->setPosition(x, y);
}

void SFMLGame::initialiserZones() {
    _zones.creerZonesStandard();
}

void SFMLGame::initialiserCartes() {
    // Créer quelques cartes de test (en pratique, tu les chargerais depuis ta logique métier)
    
    // Exemple: créer des cartes logiques de test
    // En pratique, tu récupérerais ces cartes depuis ta Partie/Joueur
    Carte* carte1 = new Carte();
    carte1->setName("Soldat Impérial");
    carte1->setFaction(Imperiale);
    carte1->setCoupOr(3);
    
    Carte* carte2 = new Carte();
    carte2->setName("Mage de la Guilde");
    carte2->setFaction(Guilde);
    carte2->setCoupOr(5);
    
    Carte* carte3 = new Carte();
    carte3->setName("Bête Sauvage");
    carte3->setFaction(Sauvage);
    carte3->setCoupOr(2);
    
    // Créer les représentations graphiques
    _cartesGraphiques.emplace_back(100, 450, 80, 120, carte1);
    _cartesGraphiques.emplace_back(200, 450, 80, 120, carte2);
    _cartesGraphiques.emplace_back(300, 450, 80, 120, carte3);
    
    // Enregistrer dans le gestionnaire
    _gestionnaireCartes.creerCarteGraphique(carte1, 100, 450);
    _gestionnaireCartes.creerCarteGraphique(carte2, 200, 450);
    _gestionnaireCartes.creerCarteGraphique(carte3, 300, 450);
}