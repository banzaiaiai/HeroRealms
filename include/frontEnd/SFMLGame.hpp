#ifndef SFMLGAME_H
#define SFMLGAME_H

#include <SFML/Graphics.hpp>
#include "backEnd/Carte/Carte.hpp"
#include "CarteGraphique.hpp"
#include "ZoneCarte.hpp"
#include "GestionnaireZones.hpp"
#include "GestionnaireCartesGraphiques.hpp"
#include <vector>
#include "backEnd/Joueur.hpp"
#include <memory>

class SFMLGame {
private:
    sf::RenderWindow _window;
    std::vector<CarteGraphique> _cartesGraphiques;
    GestionnaireZones _zones;
    GestionnaireCartesGraphiques _gestionnaireCartes;
    CarteGraphique* _carteSelectionnee;
    ZoneCarte* _zoneSource;
    sf::Vector2f _positionOriginale;

public:
    SFMLGame();
    ~SFMLGame();

    void gameLoop();

private:
    void processEvents();
    void handleMouseClick(int mouseX, int mouseY);
    void handleMouseRelease(int mouseX, int mouseY);
    void update();
    void render();
    
    bool deplacementValide(const std::string& source, const std::string& cible, Carte* carte);
    void appliquerDeplacementLogique(Carte* carte, const std::string& zoneCible);
    void deplacerCarteGraphique(CarteGraphique* carte, ZoneCarte* zone);
    void initialiserCartes();
    void initialiserZones();
};

#endif // SFMLGAME_H