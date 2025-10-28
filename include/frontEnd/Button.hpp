#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Button {
private:
    sf::RectangleShape shape;
    sf::Text text;
    sf::Font font;
    bool isHovered;

public:
    Button(const std::string& buttonText, sf::Vector2f position, sf::Vector2f size) {
        // Charger la police (à adapter selon ton système)
        if (!font.loadFromFile("arial.ttf")) {
            std::cout << "Erreur chargement police" << std::endl;
        }
        
        // Configuration du rectangle
        shape.setSize(size);
        shape.setPosition(position);
        shape.setFillColor(sf::Color(70, 70, 70));
        shape.setOutlineThickness(2);
        shape.setOutlineColor(sf::Color::White);
        
        // Configuration du texte
        text.setFont(font);
        text.setString(buttonText);
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::White);
        
        // Centrer le texte dans le bouton
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.left + textBounds.width/2.0f, 
                      textBounds.top + textBounds.height/2.0f);
        text.setPosition(position.x + size.x/2.0f, position.y + size.y/2.0f);
        
        isHovered = false;
    }
    
    void draw(sf::RenderWindow& window) {
        window.draw(shape);
        window.draw(text);
    }
    
    bool isMouseOver(sf::RenderWindow& window) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
        return shape.getGlobalBounds().contains(worldPos);
    }
    
    void update(sf::RenderWindow& window) {
        if (isMouseOver(window)) {
            if (!isHovered) {
                shape.setFillColor(sf::Color(100, 100, 100));
                isHovered = true;
            }
        } else {
            if (isHovered) {
                shape.setFillColor(sf::Color(70, 70, 70));
                isHovered = false;
            }
        }
    }
    
    bool isClicked(sf::RenderWindow& window) {
        return isMouseOver(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left);
    }
};
#endif