#include "frontEnd/GestionnaireZones.hpp"
#include "backEnd/Partie.hpp"
#include "backEnd/Joueur.hpp"
#include <iostream>

GestionnaireZones::GestionnaireZones() {}

void GestionnaireZones::creerZonesStandard() {
    // Zones pour un jeu à 2 joueurs
    _zones.push_back(std::make_unique<ZoneCarte>(150, 640, 800, 150, "main_joueur1", sf::Color(0, 0, 255, 50)));
    _zones.push_back(std::make_unique<ZoneCarte>(50, 485, 1100, 150, "plateau_joueur1", sf::Color(0, 255, 0, 50)));
    _zones.push_back(std::make_unique<ZoneCarte>(1060, 640, 80, 120, "pioche_joueur1", sf::Color(255, 255, 0, 50)));
    _zones.push_back(std::make_unique<ZoneCarte>(960, 640, 80, 120, "defausse_joueur1", sf::Color(255, 0, 0, 50)));

    _zones.push_back(std::make_unique<ZoneCarte>(150, 20, 800, 150, "main_joueur2", sf::Color(255, 0, 0, 50)));
    _zones.push_back(std::make_unique<ZoneCarte>(50, 175, 1100, 150, "plateau_joueur2", sf::Color(0, 255, 100, 50)));
    _zones.push_back(std::make_unique<ZoneCarte>(1060, 20, 80, 120, "pioche_joueur2", sf::Color(255, 200, 0, 50)));
    _zones.push_back(std::make_unique<ZoneCarte>(960, 20, 80, 120, "defausse_joueur2", sf::Color(200, 0, 0, 50)));
    
    _zones.push_back(std::make_unique<ZoneCarte>(400, 330, 500, 145, "marche0", sf::Color(255, 165, 0, 50)));
    
    // Mettre à jour la map de recherche
    for (auto& zone : _zones) {
        _zonesParNom[zone->getNom()] = zone.get();
    }
}

void GestionnaireZones::lierPartie(Partie* partie) {
    if (!partie) return;
    mettreAJourZones(partie);
}

void GestionnaireZones::mettreAJourZones(Partie* partie) {
    if (!partie) return;
    
    // Vider toutes les zones
    for (auto& zone : _zones) {
        zone->viderCartes();
    }
    
    // Remplir avec les cartes de la partie
    // NOTE: Tu devras adapter cette partie selon ta structure exacte
    auto& joueurs = partie->getListJoueur();
    
    for (size_t i = 0; i < joueurs.size(); i++) {
        std::string suffixe = "_joueur" + std::to_string(i + 1);
        
        // Exemple d'utilisation (à adapter selon tes méthodes)
        
        auto zoneMain = getZoneParNom("main" + suffixe);
        if (zoneMain) {
            for (auto& carte : joueurs[i].getMain()) {
                zoneMain->ajouterCarteLogique(&carte);
            }
        }
        
        auto zoneTerrain = getZoneParNom("plateau" +suffixe);
        if (zoneTerrain) {
            for (auto& carte : joueurs[i].getPlateau()) {
                zoneTerrain->ajouterCarteLogique(&carte);
            }
        }
        auto zoneMarche = getZoneParNom("marche0");
        if (zoneMarche) {
            for (auto& carte : partie->getRiviere()) {
                zoneMarche->ajouterCarteLogique(&carte);
            }
        }
      
        
    }
    
    //std::cout << "Zones mises à jour avec la partie" << std::endl;
}

ZoneCarte* GestionnaireZones::getZoneContenant(const sf::Vector2f& point) {
    for (auto& zone : _zones) {
        if (zone->contient(point)) {
            return zone.get();
        }
    }
    return nullptr;
}

ZoneCarte* GestionnaireZones::getZoneParNom(const std::string& nom) {
    auto it = _zonesParNom.find(nom);
    return (it != _zonesParNom.end()) ? it->second : nullptr;
}

void GestionnaireZones::dessinerZones(sf::RenderWindow& window) {
    for (auto& zone : _zones) {
        zone->dessiner(window);
    }
}