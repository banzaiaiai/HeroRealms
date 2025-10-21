#ifndef SFMLGAME_H
#define SFMLGAME_H

#include <SFML/Graphics.hpp>
#include "backEnd/Carte/Carte.hpp"
#include "backEnd/Joueur.hpp"
#include "backEnd/Partie.hpp"
#include "CarteGraphique.hpp"
#include "GestionnaireZones.hpp"
#include "frontEnd/ZoneCarte.hpp"
#include "frontEnd/Overlay.hpp"
#include <vector>
#include <memory>
#include <map>

class Overlay;

class SFMLGame {
private:
    sf::RenderWindow _window;
    Partie* _partie;  // Référence vers la logique du jeu
    
    GestionnaireZones _zones;
    std::map<Carte*, std::unique_ptr<CarteGraphique>> _cartesGraphiques;
    
    CarteGraphique* _carteSelectionnee;
    ZoneCarte* _zoneSource;
    sf::Vector2f _positionOriginale;


public:
    SFMLGame(Partie* partie = nullptr);
    ~SFMLGame();

    Overlay _overlay;
    void setPartie(Partie* partie);
    void gameLoop();

private:
    void processEvents();
    void handleMouseClick(int mouseX, int mouseY);
    void handleMouseRelease(int mouseX, int mouseY);
    void update();
    void render();
    
    void synchroniserAffichage();  // Met à jour l'affichage depuis la logique
    void creerCarteGraphique(Carte* carte);
    void supprimerCarteGraphique(Carte* carte);
    
    bool deplacementValide(ZoneCarte* source, ZoneCarte* cible, Carte* carte);
    void appliquerDeplacementLogique(Carte* carte, ZoneCarte* source, ZoneCarte* cible);
};

#endif
