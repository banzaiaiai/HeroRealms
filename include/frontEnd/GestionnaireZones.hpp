#ifndef GESTIONNAIRE_ZONES_H
#define GESTIONNAIRE_ZONES_H

#include "ZoneCarte.hpp"
#include <vector>
#include <memory>
#include <map>

// Forward declarations
class Partie;
class Joueur;

class GestionnaireZones {
private:
    std::vector<std::unique_ptr<ZoneCarte>> _zones;
    std::map<std::string, ZoneCarte*> _zonesParNom;
    
public:
    GestionnaireZones();
    
    void creerZonesStandard();
    void lierPartie(Partie* partie);
    
    ZoneCarte* getZoneContenant(const sf::Vector2f& point);
    ZoneCarte* getZoneParNom(const std::string& nom);
    
    void dessinerZones(sf::RenderWindow& window);
    void mettreAJourZones(Partie* partie);
    
    const std::vector<std::unique_ptr<ZoneCarte>>& getZones() const { return _zones; }
};

#endif