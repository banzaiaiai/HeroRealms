#ifndef ZONECARTE_HPP
#define ZONECARTE_HPP

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

class ZoneCarte {
    sf::FloatRect _zone;
    std::string _nom;
    sf::Color _couleurFond;
    public:
        ZoneCarte(float x, float y, float width, float height, 
            const std::string& nom, 
            const sf::Color& couleur = sf::Color(100, 100, 100, 100));
        bool contient(const sf::Vector2f& point) const;
        void dessiner(sf::RenderWindow& window) const;
        
        //getteur
        inline const std::string& getNom() const { return _nom; }
        inline const sf::FloatRect& getBounds() const { return _zone; }
};
#endif