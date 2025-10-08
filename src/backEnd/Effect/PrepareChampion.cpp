#include "backEnd/Effect/PrepareChampion.hpp"
#include "backEnd/Carte/Champion.hpp"  // Inclure ici dans le .cpp

PrepareChampion::PrepareChampion(Champion* champion) : _champion(champion) {}

void PrepareChampion::applyEffect() {
    if (_champion) {
        // Implémentation de la préparation du champion
    }
}
