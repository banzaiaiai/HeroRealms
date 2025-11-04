#ifndef DISCARDCARD_H
#define DISCARDCARD_H

#include "backEnd/Effect/IEffect.hpp"
#include "backEnd/Joueur.hpp"

class DiscardCard : public IEffect {
private:
    int _count;

public:
    DiscardCard(int count=0);
    ~DiscardCard();
    void applyEffect(Joueur *jouer) override;
};

#endif // DISCARDCARD_H
