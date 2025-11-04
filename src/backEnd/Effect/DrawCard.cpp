#include "backEnd/Effect/DrawCard.hpp"
#include "backEnd/Joueur.hpp"

DrawCard::DrawCard(int count) : _count(count) {}

void DrawCard::applyEffect(Joueur *joueur){
    joueur->piocher(_count);
}
