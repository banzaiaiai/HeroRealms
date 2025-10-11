#ifndef CARTE_H
#define CARTE_H

#include "backEnd/Effect/IEffect.hpp"

#include <string>
#include <map>
#include <vector>
#include <memory>
#include <type_traits>

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
    std::map<EventType, std::vector<std::unique_ptr<IEffect>>> _trigger;

public:
    Carte();
    ~Carte();
    //virtual void effect(enum effect) = 0;
    //void trigger(EventType, EffectContext);
    void addTrigger(EventType eventType,
                    std::vector<std::unique_ptr<IEffect>> effects);

    // Supprimer la copie
    Carte(const Carte&) = delete;
    Carte& operator=(const Carte&) = delete;

    // Autoriser le move
    Carte(Carte&&) noexcept = default;
    Carte& operator=(Carte&&) noexcept = default;

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

    // Template
    template <typename... Effects>
    static std::vector<std::unique_ptr<IEffect>> makeEffects(Effects&&... effects) {
        std::vector<std::unique_ptr<IEffect>> v;
        v.reserve(sizeof...(effects));
        // fold expression (C++17)
        (v.push_back(std::make_unique<typename std::decay<Effects>::type>(
             std::forward<Effects>(effects))), ...);
        return v;
    }
};

#endif // CARTE_H
