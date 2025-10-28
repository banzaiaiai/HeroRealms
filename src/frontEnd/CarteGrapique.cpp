#include "frontEnd/CarteGraphique.hpp"

CarteGraphique::CarteGraphique(float x, float y, float width, float height, const Carte* carteLogique)
    :  _isSelected(false) ,_carteLogique(carteLogique)
    
    {
    
    _shape.setPosition(x, y);
    _shape.setSize(sf::Vector2f(width, height));
    _shape.setFillColor(sf::Color::White);
    _shape.setOutlineColor(sf::Color::Black);
    _shape.setOutlineThickness(2.f);
}

CarteGraphique::CarteGraphique(float width, float height, const Carte* carteLogique)
    :  _isSelected(false) ,_carteLogique(carteLogique)
    
    {
    _shape.setSize(sf::Vector2f(width, height));
    _shape.setFillColor(sf::Color::White);
    _shape.setOutlineColor(sf::Color::Black);
    _shape.setOutlineThickness(2.f);
}

bool CarteGraphique::contains(const sf::Vector2f& point) const {
    return _shape.getGlobalBounds().contains(point);
}

void CarteGraphique::setSelected(bool selected) {
    _isSelected = selected;
    if (_isSelected) {
        _shape.setOutlineColor(sf::Color::Yellow);
        _shape.setOutlineThickness(4.f);
    } else {
        _shape.setOutlineColor(sf::Color::Black);
        _shape.setOutlineThickness(2.f);
    }
}

void CarteGraphique::draw(sf::RenderWindow& window) const {
    window.draw(_shape);
    // Ici tu pourrais aussi dessiner le texte (nom, coût, etc.)
}

void CarteGraphique::setPosition(float x, float y) {
    _shape.setPosition(x, y);
}

sf::Vector2f CarteGraphique::getPosition() const {
    return _shape.getPosition();
}

void CarteGraphique::updateAppearance() {
    if (!_carteLogique) return;
    
    // Met à jour l'apparence basée sur l'état logique
    // Exemple : griser la carte si elle ne peut pas être jouée
}