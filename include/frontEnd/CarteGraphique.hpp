#ifndef CARTE_GRAPHIQUE_H
#define CARTE_GRAPHIQUE_H

#include <SFML/Graphics.hpp>
#include "backEnd/Carte/Carte.hpp"

class CarteGraphique {
private:
    sf::RectangleShape _shape;
    sf::Texture _texture;
    sf::Text _texteNom;
    sf::Text _texteCout;
    bool _isSelected;
    Carte* _carteLogique;  // Référence vers la logique métier
    
public:
    CarteGraphique(float x, float y, float width, float height, 
                   Carte* carteLogique, const std::string& texturePath = "");
    
    // Méthodes graphiques
    bool contains(const sf::Vector2f& point) const;
    void setSelected(bool selected);
    void draw(sf::RenderWindow& window) const;
    void setPosition(float x, float y);
    sf::Vector2f getPosition() const;
    sf::Vector2f getSize() const { return _shape.getSize(); }
    
    // Lien avec la logique
    Carte* getCarteLogique() const { return _carteLogique; }
    void updateAppearance(); // Met à jour l'apparence selon l'état logique
};

#endif