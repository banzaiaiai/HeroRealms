#include "frontEnd/Overlay.hpp"

Overlay::Overlay() {
    _background.setPosition(0, 0);
    _background.setSize(sf::Vector2f(1200, 800));
    _background.setFillColor(sf::Color(0, 0, 0, 150));

}

