
#ifndef OVERLAY_H
#define OVERLAY_H

#include <SFML/Graphics.hpp>
#include "backEnd/Carte/Carte.hpp"
#include "frontEnd/ZoneCarte.hpp"
#include <vector>

class Overlay{
    friend class SFMLGame;
private:
    sf::RectangleShape _background;
    ZoneCarte _zoneCarte = ZoneCarte(100, 100, 1000, 600, "Overlay");
    bool _isOverlay = false;

public:
    Overlay();
    ~Overlay() {};
    bool getIsOverlay() { return _isOverlay; };

    Carte* openOverlay(std::vector<Carte*> listCarte);

};

#endif

