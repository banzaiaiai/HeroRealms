#ifndef RECUPCARD_H
#define RECUPCARD_H

#include "backEnd/Carte/Carte.hpp"
#include "backEnd/Effect/IEffect.hpp"
#include "backEnd/Joueur.hpp"

class RecupCard : public IEffect {
private:
    int _count;
    TypeCarte _typecarte;
    ZoneType _source;
    ZoneType _direction;
public:
    RecupCard(int count=0,TypeCarte type=TypeCarte::Tous, ZoneType source=ZoneType::Main, ZoneType direction=ZoneType::Main);
    ~RecupCard();
    void applyEffect(Joueur *joueur) override;

    // Getters
    inline int getCount() const { return _count; }

    // Setters
    inline void setCount(int count) { _count = count; }
};

#endif // RECUPCARD_H
