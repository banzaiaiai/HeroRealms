#include "backEnd/Effect/StunCard.hpp"
#include "backEnd/Carte/Champion.hpp"
#include "backEnd/Joueur.hpp"
#include "frontEnd/Overlay.hpp"
#include "backEnd/Partie.hpp"

StunCard::StunCard(int duration) : _duration(duration) 
{

}
StunCard::~StunCard() {}
void StunCard::applyEffect(Joueur *joeur){
    Overlay overlay;
    while (true) {
        Partie *partie = joeur->getPartie();
        Joueur* autreJoueur = partie->getAutreJoueurActuelle();
        int carteId = overlay.openOverlay("SelectChampion", autreJoueur->getPlateau());
        if (carteId == -1) {
            std::cerr << "Aucune carte sélectionnée pour le stun." << std::endl;
            continue; // Sortir si aucune carte n'est sélectionnée 
        }
        Carte* carteJouee = joeur->getCarteById(carteId);
        if (!carteJouee) {
            std::cerr << "Probléme de carte dans le stun: id introuver"<<std::endl;
            continue;
        }
        Champion* ch = dynamic_cast<Champion*>(carteJouee);
        if (!ch) {
            std::cerr << "La carte ciblée n'est pas un Champion" << std::endl;
            continue;
        }
        ch->setActiver(true);
        std::cout << "Champion stun avec succès" << std::endl;
        break;
    }
}
