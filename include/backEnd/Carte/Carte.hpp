#ifndef CARTE_HPP
#define CARTE_HPP

#include "backEnd/Joueur.hpp"

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <iostream>

// Forward declaration
class IEffect;
class Partie;
enum class EventType {
    OnPlay,
    OnTurnStart,
    OnAllyEnter,
    OnDelete,
    OnEngenge
};

enum class Faction {
    Neutre,
    Imperiale,
    Guilde,
    Necros,
    Sauvage
};

/**
 * Classe Carte - Pure logique métier
 * Identifiable par un ID unique
 * NE CONTIENT AUCUNE RÉFÉRENCE À L'AFFICHAGE
 */
class Carte {
private:
    static int _nextId;  // Compteur global pour générer des IDs uniques
    
    int _id;
    std::string _name;
    int _coupOr;
    Faction _faction;
    std::map<EventType, std::vector<std::shared_ptr<IEffect>>> _trigger;

public:
    // methode metier

    void jouer(Joueur *joueur);
    void jouerFaction(Joueur *joueur);
    void jouerEngager(Joueur* joueur);
    void declencherEffets(EventType eventType, Joueur* joueur);
    // Constructeur par défaut
    Carte();
    
    // Constructeur avec paramètres
    Carte(const std::string& name, int coupOr, Faction faction = Faction::Neutre);
    
    // Destructeur
    ~Carte();
    
    // Copie interdite (pour éviter les problèmes d'ID dupliqués)
    Carte(const Carte&) = delete;
    Carte& operator=(const Carte&) = delete;
    
    // Move autorisé
    Carte(Carte&& other) noexcept;
    Carte& operator=(Carte&& other) noexcept;
    
    // Getters
    int getId() const { return _id; }
    std::string getName() const { return _name; }
    int getCoupOr() const { return _coupOr; }
    Faction getFaction() const { return _faction; }
    
    // Setters
    void setName(const std::string& name) { _name = name; }
    void setCoupOr(int cout) { _coupOr = cout; }
    void setFaction(Faction faction) { _faction = faction; }
    
    // Gestion des effets
    void addTrigger(EventType eventType, std::vector<std::shared_ptr<IEffect>> effects);
    const std::vector<std::shared_ptr<IEffect>>* getEffects(EventType eventType) const;
    
    // Comparaison par ID uniquement
    bool operator==(const Carte& other) const { return _id == other._id; }
    bool operator!=(const Carte& other) const { return _id != other._id; }

    // methode de verification 
    virtual bool estChampion() const  { return false; }
};

#endif // CARTE_HPP
