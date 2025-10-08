#ifndef DISCARDCARD_H
#define DISCARDCARD_H

#include "backEnd/Effect/IEffect.hpp"

class DiscardCard : public IEffect {
private:
    int _count;

public:
    DiscardCard(int count=0);
    ~DiscardCard();
    void applyEffect() override;

    // Getters
    inline int getCount() const { return _count; }

    // Setters
    inline void setCount(int count) { _count = count; }
};

#endif // DISCARDCARD_H
