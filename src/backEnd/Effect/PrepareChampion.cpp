#include "backEnd/Effect/PrepareChampion.hpp"
#include "backEnd/Carte/Champion.hpp"  // Inclure ici dans le .cpp
#include "backEnd/Joueur.hpp"
#include "frontEnd/Overlay.hpp"

PrepareChampion::PrepareChampion() {
}

void PrepareChampion::applyEffect(Joueur *joueur) {
    
    Overlay overlay;
    while (true) {
        int carteId = overlay.openOverlay("SelectChampion", joueur->getPlateau());
        if (carteId == -1) {
            std::cerr << "Aucune carte sélectionnée pour l'engagement." << std::endl;
            continue; // Sortir si aucune carte n'est sélectionnée    
        }
        Carte* carteJouee = joueur->getCarteById(carteId);
        if (!carteJouee) {
            std::cerr << "Probléme de carte dans l'engagement: id introuvable sur le plateau" << std::endl;
            continue; 
        }
        Champion* ch = dynamic_cast<Champion*>(carteJouee);
        if (!ch) {
            std::cerr << "La carte ciblée n'est pas un Champion" << std::endl;
            continue;
        }
        if(!ch->getActiver()){
            std::cerr << "La carte ciblée est pas engagée ça cere a rien" << std::endl;
            continue;
        }
        ch->setActiver(false);
        std::cout << "Champion désengagé avec succès" << std::endl;
        break;
    }
}
