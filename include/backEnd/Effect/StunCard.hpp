#ifndef STUNCARD_H
#define STUNCARD_H

#include "backEnd/Effect/IEffect.hpp"
#include "backEnd/Joueur.hpp"

class StunCard : public IEffect {
public:
    StunCard() {};
    ~StunCard();
    void applyEffect(Joueur *joueur) override;
};

#endif // STUNCARD_H
