
#ifndef OVERLAY_H
#define OVERLAY_H

#include <SFML/Graphics.hpp>
#include "backEnd/Carte/Carte.hpp"
#include "frontEnd/ZoneCarte.hpp"
#include "frontEnd/GestionnaireZones.hpp"
#include "frontEnd/CarteGraphique.hpp"
#include <vector>

class Overlay {
private:
    sf::RenderWindow _window;
    ZoneCarte _zoneCarte;
    std::vector<const Carte*> _listCarte;
    std::vector<CarteGraphique> _listCarteGraphique;

    void render();

public:
    Overlay();
    ~Overlay() {};

    const Carte* openOverlay(std::vector<const Carte*> listCarte,
                             std::string titre = "overlay");

};

#endif

