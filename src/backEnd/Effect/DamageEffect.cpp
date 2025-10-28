#include "backEnd/Effect/DamageEffect.hpp"
#include "backEnd/Partie.hpp"
#include "backEnd/Joueur.hpp"

DamageEffect::DamageEffect(int damage) : _damage(damage) {}

void DamageEffect::applyEffect(Joueur *joueur) {
    joueur->setDegat(_damage);
}
