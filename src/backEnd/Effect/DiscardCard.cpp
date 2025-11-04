#include "backEnd/Effect/DiscardCard.hpp"
#include "backEnd/Joueur.hpp"
#include "backEnd/Partie.hpp"

DiscardCard::DiscardCard(int count) : _count(count)
{

}
void DiscardCard::applyEffect(Joueur *joeur){
    Partie *partie = joeur->getPartie();
    partie->getAutreJoueurActuelle()->addCompteurDefausse(_count);
}
DiscardCard::~DiscardCard() {}
