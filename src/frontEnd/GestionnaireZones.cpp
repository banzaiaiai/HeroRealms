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
    
    _zones.push_back(std::make_unique<ZoneCarte>(400, 330, 500, 145, "marche", sf::Color(255, 165, 0, 50)));
    
    // Mettre à jour la map de recherche
    for (auto& zone : _zones) {
        _zonesParNom[zone->getNom()] = zone.get();
    }
}

// inutilee dans cette version
void GestionnaireZones::lierPartie(Partie* partie) {
    if (!partie) return;
    mettreAJourZones(partie);
}

void GestionnaireZones::mettreAJourZones(Partie* partie) {
    if (!partie) return;
    
    // Vider toutes les zones d'observation
    for (auto& zone : _zones) {
        zone->viderCartes();
    }
    
    // Récupérer les joueurs
    auto& joueurs = partie->getListJoueur();
    
    // Synchroniser les zones de chaque joueur
    for (size_t i = 0; i < joueurs.size(); i++) {
        std::string suffixe = "_joueur" + std::to_string(i + 1);
        
        // MAIN
        auto zoneMain = getZoneParNom("main" + suffixe);
        if (zoneMain) {
            // Obtenir les pointeurs const vers les cartes
            auto cartesMain = joueurs[i].getMain();
            for (const Carte* carte : cartesMain) {
                zoneMain->observerCarte(carte);
            }
        }
        
        // PLATEAU
        auto zonePlateau = getZoneParNom("plateau" + suffixe);
        if (zonePlateau) {
            auto cartesPlateau = joueurs[i].getPlateau();
            for (const Carte* carte : cartesPlateau) {
                zonePlateau->observerCarte(carte);
            }
        }
        
        // PIOCHE
        auto zonePioche = getZoneParNom("pioche" + suffixe);
        if (zonePioche) {
            auto cartesPioche = joueurs[i].getPioche();
            // Afficher seulement le dos de la dernière carte
            if (!cartesPioche.empty()) {
                zonePioche->observerCarte(cartesPioche.back());
            }
        }
        
        // DEFAUSSE
        auto zoneDefausse = getZoneParNom("defausse" + suffixe);
        if (zoneDefausse) {
            auto cartesDefausse = joueurs[i].getDefausse();
            // Afficher seulement la dernière carte
            if (!cartesDefausse.empty()) {
                zoneDefausse->observerCarte(cartesDefausse.back());
            }
        }
    }
    
    // MARCHE (rivière commune)
    auto zoneMarche = getZoneParNom("marche");
    if (zoneMarche) {
        auto cartesRiviere = partie->getRiviere();
        for (const Carte* carte : cartesRiviere) {
            zoneMarche->observerCarte(carte);
        }
    }
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
        if (zone->getNom() != "overlay"){
            zone->dessiner(window);
        }
    }
}

const std::vector<std::unique_ptr<ZoneCarte>>& GestionnaireZones::getZones() const {
    return _zones;
}
