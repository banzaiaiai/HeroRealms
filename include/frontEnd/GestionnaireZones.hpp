#ifndef GESTIONNAIREZONES_HPP
#define GESTIONNAIREZONES_HPP

#include <vector>
#include <map>
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "frontEnd/ZoneCarte.hpp"

class Partie;

/**
 * GestionnaireZones - Gère toutes les zones graphiques du jeu
 * Synchronise les zones avec l'état de la partie
 */
class GestionnaireZones {
private:
    std::vector<std::unique_ptr<ZoneCarte>> _zones;
    std::map<std::string, ZoneCarte*> _zonesParNom;

public:
    GestionnaireZones();
    
    /**
     * Crée les zones standard pour un jeu à 2 joueurs
     */
    void creerZonesStandard();
    
    /**
     * Lie le gestionnaire à une partie
     */
    void lierPartie(Partie* partie);
    
    /**
     * Met à jour toutes les zones avec l'état actuel de la partie
     * Vide et remplit les zones d'observation
     */
    void mettreAJourZones(Partie* partie);
    
    /**
     * Trouve la zone contenant un point
     */
    ZoneCarte* getZoneContenant(const sf::Vector2f& point);
    
    /**
     * Récupère une zone par son nom
     */
    ZoneCarte* getZoneParNom(const std::string& nom);
    
    /**
     * Retourne toutes les zones
     */
    const std::vector<std::unique_ptr<ZoneCarte>>& getZones() const;
    
    /**
     * Dessine toutes les zones
     */
    void dessinerZones(sf::RenderWindow& window);
};

#endif // GESTIONNAIREZONES_HPP