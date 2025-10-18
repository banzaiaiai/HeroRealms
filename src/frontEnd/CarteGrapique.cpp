#include "frontEnd/CarteGraphique.hpp"

CarteGraphique::CarteGraphique(float x, float y, float width, float height, 
                               Carte* carteLogique, const std::string& texturePath)
    : _carteLogique(carteLogique), _isSelected(false) {
    
    _shape.setPosition(x, y);
    _shape.setSize(sf::Vector2f(width, height));
    
    // Charger la texture si disponible
    if (!texturePath.empty() && _texture.loadFromFile(texturePath)) {
        _shape.setTexture(&_texture);
    } else {
        // Couleur par défaut basée sur la faction
        if (_carteLogique) {
            switch(_carteLogique->getFaction()) {
                case Imperiale: _shape.setFillColor(sf::Color(200, 200, 255)); break;
                case Guilde: _shape.setFillColor(sf::Color(255, 255, 200)); break;
                case Necros: _shape.setFillColor(sf::Color(100, 100, 100)); break;
                case Sauvage: _shape.setFillColor(sf::Color(200, 255, 200)); break;
                default: _shape.setFillColor(sf::Color::White);
            }
        } else {
            _shape.setFillColor(sf::Color::White);
        }
    }
    
    _shape.setOutlineThickness(2.f);
    _shape.setOutlineColor(sf::Color::Black);
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