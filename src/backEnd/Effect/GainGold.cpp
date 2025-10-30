#include "backEnd/Effect/GainGold.hpp"
#include "backEnd/Joueur.hpp"

GainGold::GainGold(int gold) : _gold(gold) {}

void GainGold::applyEffect(Joueur *joueur) {
    int montant = _gold;
    joueur->ajouterOr(montant);
}
