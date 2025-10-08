#ifndef HEALEFFECT_H
#define HEALEFFECT_H

#include "backEnd/Effect/IEffect.hpp"

class HealEffect : public IEffect {
private:
    int _heal;

public:
    HealEffect(int heal = 0);
    ~HealEffect() override = default;
    
    void applyEffect() override;

    inline int getHeal() const { return _heal; }
    inline void setHeal(int heal) { _heal = heal; }
};

#endif // HEALEFFECT_H
