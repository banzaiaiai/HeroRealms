#ifndef HEALEFFECT_H
#define HEALEFFECT_H

#include "backEnd/Effect/IEffect.hpp"
#include "backEnd/Joueur.hpp"
class HealEffect : public IEffect {
private:
    int _heal;
    OccurenceType _occurenceType;
    int _valueByOccurence;

public:
    HealEffect(int heal, OccurenceType occurenceType = OccurenceType::None,
                 int valueByOccurence = 0):
        _heal(heal),
        _occurenceType(occurenceType),
        _valueByOccurence(valueByOccurence) {};
    ~HealEffect() override = default;

    void applyEffect(Joueur *joueur) override;
};

#endif // HEALEFFECT_H
