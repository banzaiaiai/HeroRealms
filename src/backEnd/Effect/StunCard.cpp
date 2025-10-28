#include "backEnd/Effect/StunCard.hpp"
#include "backEnd/Joueur.hpp"


StunCard::StunCard(int duration) : _duration(duration) 
{

}
StunCard::~StunCard() {}
void StunCard::applyEffect(Joueur *joeur){}
