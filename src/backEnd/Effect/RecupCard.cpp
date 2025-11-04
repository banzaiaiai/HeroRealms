#include "backEnd/Effect/RecupCard.hpp"
#include "backEnd/Effect/NextCardRecup.hpp"
#include "backEnd/Joueur.hpp"
#include "frontEnd/Overlay.hpp"

RecupCard::RecupCard(int count,TypeCarte type, ZoneType source, ZoneType direction) : 
    _count(count),
    _typecarte(type),
    _source(source),
    _direction(direction)

{

}

void RecupCard::applyEffect(Joueur *joeur){
    Overlay overlay;
    int carteID = overlay.openOverlay("effet",joeur->getZone(_source));
    Carte * carte =joeur->getCarteById(carteID);
    if(_typecarte==TypeCarte::Champion && carte->estChampion())
    {
        joeur->deplacerCarte(carteID, _source, _direction);
    }
    else if (_typecarte!=TypeCarte::Champion) {
        joeur->deplacerCarte(carteID, _source, _direction);
    }
}
RecupCard::~RecupCard() {}
