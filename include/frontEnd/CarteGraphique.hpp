#ifndef CARTE_GRAPHIQUE_H
#define CARTE_GRAPHIQUE_H

#include <SFML/Graphics.hpp>
#include "backEnd/Carte/Carte.hpp"

class CarteGraphique {
private:
    sf::Sprite _sprite;
    bool _isSelected;
    const Carte* _carteLogique;  // Référence vers la logique métier
    
public:
    // Le constructeur doit matcher exactement l'appel
    CarteGraphique(float x, float y, float width, float height, const Carte* carteLogique);
    CarteGraphique(float width, float height, const Carte* carteLogique);
    // Méthodes graphiques
    bool contains(const sf::Vector2f& point) const;
    void setSelected(bool selected);
    void draw(sf::RenderWindow& window) const;
    void setPosition(float x, float y);
    sf::Vector2f getPosition() const;
    sf::Vector2f getSize() const;
    
    // Lien avec la logique
    const Carte* getCarteLogique() const { return _carteLogique; }
    void updateAppearance(); // Met à jour l'apparence selon l'état logique
    sf::FloatRect getGlobalBounds() const {
        return _sprite.getGlobalBounds();
    }

    // getteur
    bool getIsSelected(){
        return  _isSelected;
    }
};

#endif
