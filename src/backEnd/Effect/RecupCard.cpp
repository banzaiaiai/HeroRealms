#include "backEnd/Effect/RecupCard.hpp"
#include "backEnd/Carte/Carte.hpp"
#include "backEnd/Joueur.hpp"

RecupCard::RecupCard(int count,TypeCarte typecarte, ZoneType zone): 
_count(count),
_typecarte(typecarte),
_zone(zone)
{
  
}
void RecupCard::applyEffect(Joueur *joeur)
{
 joeur->setNextAchat(true);   
 if(_typecarte!=TypeCarte::Tous){
     joeur->setTypecarteRecup(_typecarte);
 }
    joeur->setZoneRecup(_zone);
}
RecupCard::~RecupCard() {}
