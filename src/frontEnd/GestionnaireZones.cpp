#include "frontEnd/GestionnaireZones.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

void GestionnaireZones::dessinerZones(sf::RenderWindow & window)
{
            for (auto& zone : _zones) {
                zone->dessiner(window);
            }
}

void GestionnaireZones::creerZonesStandard()
{
            // Main du joueur
            ajouterZone(std::make_unique<ZoneCarte>(50, 400, 700, 150, "main_joueur", sf::Color(0, 0, 255, 50)));
            
            // Plateau de jeu
            ajouterZone(std::make_unique<ZoneCarte>(200, 200, 400, 150, "plateau", sf::Color(0, 255, 0, 50)));
            
            // Pioche
            ajouterZone(std::make_unique<ZoneCarte>(650, 50, 80, 120, "pioche", sf::Color(255, 255, 0, 50)));
            
            // Défausse
            ajouterZone(std::make_unique<ZoneCarte>(550, 50, 80, 120, "defausse", sf::Color(255, 0, 0, 50)));
            
            // Rivière/marché
            ajouterZone(std::make_unique<ZoneCarte>(50, 50, 450, 120, "marche", sf::Color(255, 165, 0, 50)));
}