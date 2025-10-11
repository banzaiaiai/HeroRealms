#ifndef CARTE_H
#define CARTE_H

#include "backEnd/Effect/IEffect.hpp"

#include <string>
#include <map>
#include <vector>

// Forward declaration
class Joueur;

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
    Joueur* _joueur;  // POINTEUR au lieu d'objet
    std::string _name;
    enum Faction _faction;
    int _coupOr;
    std::map<EventType, std::vector<IEffect>> _trigger;

public:
    Carte();
    ~Carte();
    //virtual void effect(enum effect) = 0;
    //void trigger(EventType, EffectContext);

    // Getters
    inline Joueur* getJoueur() const { return _joueur; }  // Retourne un pointeur
    inline std::string getName() const { return _name; }
    inline Faction getFaction() const { return _faction; }
    inline int getCoupOr() const { return _coupOr; }

    // Setters
inline void setJoueur(Joueur* joueur) { _joueur = joueur; }  // Prend un pointeur
    inline void setName(std::string name) { _name = name; }
    inline void setFaction(Faction faction) { _faction = faction; }
    inline void setCoupOr(int coupOr) { _coupOr = coupOr; }

    // Operateur
    bool operator==(const Carte & other) const;
};

#endif // CARTE_H
