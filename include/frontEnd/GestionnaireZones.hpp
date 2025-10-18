#ifndef GESTIONNAIREZONES_HPP
#define GESTIONNAIREZONES_HPP

#include "frontEnd/ZoneCarte.hpp"
#include <memory>
#include <vector>
class GestionnaireZones {
    std::vector<std::unique_ptr<ZoneCarte>> _zones;
    ZoneCarte* _zoneActuelle;
    
    public: 
        GestionnaireZones() : _zoneActuelle(nullptr) {}
        
        void ajouterZone(std::unique_ptr<ZoneCarte> zone) {
            _zones.push_back(std::move(zone));
        }
        
        
        
        void dessinerZones(sf::RenderWindow& window) ;
        
        // Zones prédéfinies pour un jeu de cartes
        void creerZonesStandard() ;

        // getteur 
        ZoneCarte* getZoneContenant(const sf::Vector2f& point) {
            for (auto& zone : _zones) {
                if (zone->contient(point)) {
                    return zone.get();
                }
            }
            return nullptr;
        }
};
#endif