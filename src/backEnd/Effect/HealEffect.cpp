#include "backEnd/Effect/HealEffect.hpp"
#include "backEnd/Joueur.hpp"
#include "backEnd/Partie.hpp"

void HealEffect::applyEffect(Joueur *joueur) {
    joueur->ajouterPV(_heal);

    switch (_occurenceType) {
        case OccurenceType::Champion: {
            for (const auto& carte : joueur->getPlateau()) {
                if (carte->estChampion()) {
                    joueur->ajouterPV(_valueByOccurence);
                }
            }
            break;
        }

        default:
            break;
    };
}
