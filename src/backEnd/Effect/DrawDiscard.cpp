#include "backEnd/Effect/DrawDiscard.hpp"
#include "backEnd/Carte/Carte.hpp"
#include "backEnd/Joueur.hpp"
#include "frontEnd/Overlay.hpp"
#include <vector>

DrawDiscard::DrawDiscard(){

};

void DrawDiscard::applyEffect(Joueur *joeur){
    Carte carte("teste",0,Faction::Neutre,"assets/alternative_carte/do-nothing.jpg");
    Carte carte1("teste",0,Faction::Neutre,"assets/alternative_carte/draw-and-discard.jpg");

    std::vector<Carte> vec;
    vec.push_back(carte);
    vec.push_back(carte1);
    Overlay overlay;
    int carteId = overlay.openOverlay("draw & discard",vec);
    if(carteId!=carte.getId()){
        joeur->piocher(1);
        joeur->defausserCarte(1);
    }
}