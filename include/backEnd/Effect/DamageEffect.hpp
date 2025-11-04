#ifndef DAMAGEEFFECT_H
#define DAMAGEEFFECT_H

#include "backEnd/Effect/IEffect.hpp"
#include "backEnd/Joueur.hpp"
#include "backEnd/Carte/Carte.hpp"
#include "backEnd/Carte/Champion.hpp"

class DamageEffect : public IEffect {
private:
    int _damage;
    OccurenceType _occurenceType;
    int _valueByOccurence;

public:
    DamageEffect(int damage, OccurenceType occurenceType = OccurenceType::None,
                 int valueByOccurence = 0):
        _damage(damage),
        _occurenceType(occurenceType),
        _valueByOccurence(valueByOccurence) {};

    ~DamageEffect() override = default;
    
    void applyEffect(Joueur *joueur) override;  // Implémentation

    // Getters et setters...
    inline int getDamage() const { return _damage; }
    inline void setDamage(int damage) { _damage = damage; }
};

#endif // DAMAGEEFFECT_H
