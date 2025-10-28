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

    // Getters
    inline int getCount() const { return _count; }

    // Setters
    inline void setCount(int count) { _count = count; }
};

#endif // DRAWCARD_H
