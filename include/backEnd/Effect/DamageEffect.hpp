#ifndef DAMAGEEFFECT_H
#define DAMAGEEFFECT_H

#include "backEnd/Effect/IEffect.hpp"

class DamageEffect : public IEffect {
private:
    int _damage;

public:
    DamageEffect(int damage = 0);
    ~DamageEffect() override = default;
    
    void applyEffect(Partie *partie) override;  // Implémentation

    // Getters et setters...
    inline int getDamage() const { return _damage; }
    inline void setDamage(int damage) { _damage = damage; }
};

#endif // DAMAGEEFFECT_H
