#include "backEnd/Effect/PrepareChampion.hpp"
#include "backEnd/Carte/Champion.hpp"  // Inclure ici dans le .cpp
#include "backEnd/Joueur.hpp"

PrepareChampion::PrepareChampion(Champion* champion) : _champion(champion) {}

void PrepareChampion::applyEffect(Joueur *joueur) {
    if (_champion) {
        // Implémentation de la préparation du champion
    }
}
