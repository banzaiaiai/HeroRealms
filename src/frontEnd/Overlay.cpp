#include "frontEnd/Overlay.hpp"
#include <iostream>

Overlay::Overlay(ZoneCarte* zoneCarte) {
    _background.setPosition(0, 0);
    _background.setSize(sf::Vector2f(1200, 800));
    _background.setFillColor(sf::Color(0, 0, 0, 150));

    _zoneCarte = zoneCarte; 
}

Carte* Overlay::openOverlay(std::vector<Carte*> listCarte) {
    _isOverlay = true;
    for (auto carte : listCarte) {
        _zoneCarte->ajouterCarteLogique(carte);
    }
    std::cout << _zoneCarte->getCartesLogiques().size() << std::endl;
    return listCarte.back();
}

