#ifndef DRAWCARD_H
#define DRAWCARD_H

#include "backEnd/Effect/IEffect.hpp"
#include "backEnd/Joueur.hpp"

class DrawCard : public IEffect {
private:
    int _count;

public:
    DrawCard(int count=0);
    ~DrawCard() override = default;
    void applyEffect(Joueur * joueur) override;
};

#endif // DRAWCARD_H
