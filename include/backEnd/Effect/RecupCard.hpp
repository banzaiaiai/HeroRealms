#ifndef RECUPCARD_H
#define RECUPCARD_H

#include "backEnd/Effect/IEffect.hpp"

class RecupCard : public IEffect {
private:
    int _count;

public:
    RecupCard(int count=0);
    ~RecupCard();
    void applyEffect(Partie *partie) override;

    // Getters
    inline int getCount() const { return _count; }

    // Setters
    inline void setCount(int count) { _count = count; }
};

#endif // RECUPCARD_H
