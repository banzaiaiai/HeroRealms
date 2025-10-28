#include "backEnd/Effect/DamageEffect.hpp"
#include "backEnd/Partie.hpp"
#include "backEnd/Joueur.hpp"
#include <iostream>
#include <ostream>

DamageEffect::DamageEffect(int damage) : _damage(damage) {}

void DamageEffect::applyEffect(Joueur *joueur) {
    std::cout << "DamageEffect sur joueur: " << GLOBALjoeurActuelle << " (" << _damage << " dmg)" << std::endl;
    GLOBALjoeurActuelle->setDegat(_damage);
}
