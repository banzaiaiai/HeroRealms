#include "frontEnd/SFMLGame.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <iostream>
#include <ostream>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

SFMLGame::SFMLGame()
    : _window(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT),"teste je panique", sf::Style::Titlebar)
{
    std::cout<<"Game construit " << this << std::endl;
}

SFMLGame::~SFMLGame()
{
    std::cout<<"Game détruite " << this << std::endl;
}

void SFMLGame::gameLoop()
{
    while (_window.isOpen()) {
        sf::Event event;
        while (_window.pollEvent(event)) {
            if(event.type==sf::Event::Closed){
                _window.close();
            }
        }
        _window.display();
    }
    
}