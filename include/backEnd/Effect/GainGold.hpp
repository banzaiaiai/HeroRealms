#ifndef GAINGOLD_H
#define GAINGOLD_H

#include "backEnd/Effect/IEffect.hpp"

class GainGold : public IEffect {
private:
    int _gold;

public:
    GainGold(int gold = 0);
    ~GainGold() override = default;
    
    void applyEffect(Partie *_partie) override;

    inline int getGold() const { return _gold; }
    inline void setGold(int gold) { _gold = gold; }
};

#endif // GAINGOLD_H
