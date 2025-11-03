#ifndef RECUPCARD_H
#define RECUPCARD_H

#include "backEnd/Carte/Carte.hpp"
#include "backEnd/Effect/IEffect.hpp"
#include "backEnd/Joueur.hpp"

class RecupCard : public IEffect {
private:
    int _count;
    TypeCarte _typecarte;
    ZoneType _zone;

public:
    RecupCard(int count=0,TypeCarte typecarte=TypeCarte::Tous, ZoneType zone=ZoneType::Main);
    ~RecupCard();
    void applyEffect(Joueur *joueur) override;

    // Getters
    inline int getCount() const { return _count; }

    // Setters
    inline void setCount(int count) { _count = count; }
};

#endif // RECUPCARD_H
