#include "frontEnd/Overlay.hpp"
#include <iostream>

Overlay::Overlay(ZoneCarte* zoneCarte) {
    _background.setPosition(0, 0);
    _background.setSize(sf::Vector2f(1200, 800));
    _background.setFillColor(sf::Color(0, 0, 0, 200));

    _zoneCarte = zoneCarte; 
}

const Carte* Overlay::openOverlay(std::vector<const Carte*> listCarte) {
    _isOverlay = true;
    for (auto carte : listCarte) {
        _zoneCarte->observerCarte(carte);
    }
    return listCarte.back();
}

