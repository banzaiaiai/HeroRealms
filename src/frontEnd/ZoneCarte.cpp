#include "frontEnd/ZoneCarte.hpp"
#include "backEnd/Carte/Carte.hpp"
#include <algorithm>

ZoneCarte::ZoneCarte(float x, float y, float width, float height, 
                     const std::string& nom, sf::Color couleur)
    : _x(x), _y(y), _width(width), _height(height), 
      _nom(nom), _couleur(couleur)
{
    _shape.setPosition(x, y);
    _shape.setSize(sf::Vector2f(width, height));
    _shape.setFillColor(couleur);
    _shape.setOutlineColor(sf::Color::White);
    _shape.setOutlineThickness(2.0f);

    std::cout << "ZoneCarte '" << _nom << "' créée aux coordonnées (" 
         << _x << ", " << _y << ") avec taille (" 
         << _width << "x" << _height << ")" << std::endl;
}

ZoneCarte::~ZoneCarte() {
    // Rien à détruire, on ne possède pas les cartes
    std::cout << "ZoneCarte '" << _nom << "' détruite." << std::endl;
}

void ZoneCarte::viderCartes() {
    _cartesObservees.clear();
}

void ZoneCarte::observerCarte(const Carte* carte) {
    if (!carte) return;
    
    // Vérifier qu'elle n'est pas déjà observée
    //auto it = std::find(_cartesObservees.begin(), _cartesObservees.end(), carte);
    //if (it == _cartesObservees.end()) {
        _cartesObservees.push_back(carte);
    //}
}

void ZoneCarte::arreterObserver(const Carte* carte) {
    auto it = std::find(_cartesObservees.begin(), _cartesObservees.end(), carte);
    if (it != _cartesObservees.end()) {
        _cartesObservees.erase(it);
    }
}

bool ZoneCarte::contient(const sf::Vector2f& point) const {
    return point.x >= _x && point.x <= _x + _width &&
           point.y >= _y && point.y <= _y + _height;
}

std::vector<sf::Vector2f> ZoneCarte::calculerPositionsCartes() const {
    std::vector<sf::Vector2f> positions;
    
    if (_cartesObservees.empty()) {
        return positions;
    }
    
    const float CARD_WIDTH = 80.0f;
    const float CARD_HEIGHT = 120.0f;
    const float SPACING = 10.0f;
    
    size_t nbCartes = _cartesObservees.size();
    
    // Calcul de la disposition
    if (_nom.find("main") != std::string::npos) {
        // Disposition horizontale pour la main
        float totalWidth = nbCartes * CARD_WIDTH + (nbCartes - 1) * SPACING;
        float startX = _x + (_width - totalWidth) / 2.0f;
        float y = _y + (_height - CARD_HEIGHT) / 2.0f;
        
        for (size_t i = 0; i < nbCartes; i++) {
            positions.push_back(sf::Vector2f(
                startX + i * (CARD_WIDTH + SPACING),
                y
            ));
        }
    }
    else if (_nom.find("plateau") != std::string::npos) {
        // Disposition en grille pour le plateau
        const int CARDS_PER_ROW = 8;
        float startX = _x + SPACING;
        float startY = _y + SPACING;
        
        for (size_t i = 0; i < nbCartes; i++) {
            int row = i / CARDS_PER_ROW;
            int col = i % CARDS_PER_ROW;
            
            positions.push_back(sf::Vector2f(
                startX + col * (CARD_WIDTH + SPACING),
                startY + row * (CARD_HEIGHT + SPACING)
            ));
        }
    }
    else if (_nom.find("pioche") != std::string::npos || 
             _nom.find("defausse") != std::string::npos) {
        // Une seule position pour pioche/défausse
        float centerX = _x + (_width - CARD_WIDTH) / 2.0f;
        float centerY = _y + (_height - CARD_HEIGHT) / 2.0f;
        
        for (size_t i = 0; i < nbCartes; i++) {
            positions.push_back(sf::Vector2f(centerX, centerY));
        }
    }
    else {
        // Disposition par défaut (marché)
        float startX = _x + SPACING;
        float y = _y + (_height - CARD_HEIGHT) / 2.0f;
        
        for (size_t i = 0; i < nbCartes; i++) {
            positions.push_back(sf::Vector2f(
                startX + i * (CARD_WIDTH + SPACING),
                y
            ));
        }
    }
    
    return positions;
}

void ZoneCarte::dessiner(sf::RenderWindow& window) const {
    window.draw(_shape);
}
