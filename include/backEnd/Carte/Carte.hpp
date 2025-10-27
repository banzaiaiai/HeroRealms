#ifndef CARTE_H
#define CARTE_H

#include "backEnd/Effect/IEffect.hpp"

//#include "backEnd/Partie.hpp"
#include <string>
#include <map>
#include <vector>
#include <memory>

// Forward declarations
class Joueur;
class CarteGraphique;
class Partie;

enum EventType {
    OnPlay,
    OnTurnStart,
    OnAllyEnter,
    OnDelete
};

enum Faction {
    Imperiale,
    Guilde,
    Necros,
    Sauvage
};

class Carte {
protected:
    Joueur* _joueur;  
    std::string _name;
    enum Faction _faction;
    int _coupOr;
    std::map<EventType, std::vector<std::shared_ptr<IEffect>>> _trigger;
    CarteGraphique* _carteGraphique;  // NOUVEAU: Lien vers la représentation graphique

public:
    Carte();
    Carte(CarteGraphique* carteGraphique);
    ~Carte();
    //virtual void effect(enum effect) = 0;
    //void trigger(EventType, EffectContext);
    void addTrigger(EventType eventType, std::vector<std::shared_ptr<IEffect>> effects);
    void jouer(Partie* partie);

    // Getters
    inline Joueur* getJoueur() const { return _joueur; } 
    inline std::string getName() const { return _name; }
    inline Faction getFaction() const { return _faction; }
    inline int getCoupOr() const { return _coupOr; }
    inline CarteGraphique* getCarteGraphique() const { return _carteGraphique; }  // NOUVEAU

    // Setters
    inline void setJoueur(Joueur* joueur) { _joueur = joueur; } 
    inline void setName(std::string name) { _name = name; }
    inline void setFaction(Faction faction) { _faction = faction; }
    inline void setCoupOr(int coupOr) { _coupOr = coupOr; }
    inline void setCarteGraphique(CarteGraphique* carteGraphique) { _carteGraphique = carteGraphique; }  // NOUVEAU

    // Opérateur
    bool operator==(const Carte & other) const;
    bool operator==(const Carte *other) const;
};

#endif // CARTE_H