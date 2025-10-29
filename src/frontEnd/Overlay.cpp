#include "frontEnd/Overlay.hpp"
#include <iostream>
#include <string>

Overlay::Overlay(): _zoneCarte(0, 0, 1000, 600, "overlay",
                               sf::Color(0, 255, 0, 50)) {}

const Carte* Overlay::openOverlay(std::vector<const Carte*> listCarte,
                                  std::string titre) {
    _listCarte = listCarte;
    
    _window.create(sf::VideoMode(1000, 600),
                   titre,
                   sf::Style::Titlebar | sf::Style::Close);

    
    // donner les positions des cartes graphiques
    // rappel : taille des cartes (80, 120)
    const float CARD_WIDTH = 80.0f;
    const float CARD_HEIGHT = 120.0f;
    const float SPACING = 10.0f;
    const int MAX_PER_ROW = 10;
    const int WINDOW_WIDTH = 1000;
    const int WINDOW_HEIGHT = 600;

    const int lenListCarte = _listCarte.size();
    const int numRows = (lenListCarte + MAX_PER_ROW - 1) / MAX_PER_ROW;

    // Calculate total grid height for vertical centering
    const float totalHeight = numRows * CARD_HEIGHT + (numRows - 1) * SPACING;
    const float yOffset = (WINDOW_HEIGHT - totalHeight) / 2.0f;

    int index = 0;
    for (int j = 0; j < numRows; ++j) {
        const int cardsInRow = std::min(MAX_PER_ROW, lenListCarte - index);
        const float rowWidth = cardsInRow * CARD_WIDTH + (cardsInRow - 1) * SPACING;
        const float xOffset = (WINDOW_WIDTH - rowWidth) / 2.0f;

        for (int i = 0; i < cardsInRow; ++i) {
            const float x = xOffset + i * (CARD_WIDTH + SPACING);
            const float y = yOffset + j * (CARD_HEIGHT + SPACING);

            _listCarteGraphique.emplace_back(
                CarteGraphique(x, y, CARD_WIDTH, CARD_HEIGHT, _listCarte[index])
            );
            ++index;
        }
    }

    // Main loop
    while (_window.isOpen()) {
        sf::Event event;
        while (_window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    _window.close();
                    break;

                case sf::Event::MouseButtonReleased:
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2f mousePos = _window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                        // Chercher la carte graphique cliquée (par ID)
                        for (auto& carteGraphique : _listCarteGraphique) {
                            if (carteGraphique.contains(mousePos)) {
                                _window.close();
                                return carteGraphique.getCarteLogique();
                            }
                        }
                    }
                    break;

                default:
                    break;
            }
        }

        _window.clear();
        render();
        _window.display();
    }
    
    return nullptr;
}

void Overlay::render() {
    _zoneCarte.dessiner(_window);
    for (auto& carte : _listCarteGraphique) {
        carte.draw(_window);
    }
}


