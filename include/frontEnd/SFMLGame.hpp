#ifndef SFMLGAME_HPP
#define SFMLGAME_HPP

#include <SFML/Graphics/RenderWindow.hpp>

class SFMLGame {
    sf::RenderWindow _window;
    public:
        SFMLGame();
        ~SFMLGame();
        void gameLoop();
};
#endif