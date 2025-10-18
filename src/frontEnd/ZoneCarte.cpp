#include "frontEnd/ZoneCarte.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

ZoneCarte::ZoneCarte(float x, float y, float width, float height, 
            const std::string& nom, const sf::Color& couleur) 
            : _zone(x, y, width, height), 
            _nom(nom), _couleurFond(couleur)
{
    
}

bool ZoneCarte::contient(const sf::Vector2f& point) const 
{
        return _zone.contains(point);
}
void ZoneCarte::dessiner(sf::RenderWindow& window) const 
{
        sf::RectangleShape fond(sf::Vector2f(_zone.width, _zone.height));
        fond.setPosition(_zone.left, _zone.top);
        fond.setFillColor(_couleurFond);
        fond.setOutlineColor(sf::Color::White);
        fond.setOutlineThickness(2.f);
        window.draw(fond);
}
