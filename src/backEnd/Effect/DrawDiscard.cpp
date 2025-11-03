#include "backEnd/Effect/DrawDiscard.hpp"
#include "backEnd/Carte/Carte.hpp"
#include "backEnd/Joueur.hpp"
#include "frontEnd/Overlay.hpp"
#include <memory>
#include <vector>

DrawDiscard::DrawDiscard(){

};

void DrawDiscard::applyEffect(Joueur *joeur){
    std::vector<std::unique_ptr<Carte>> vec;
    vec.push_back(std::make_unique<Carte>("teste",0,Faction::Neutre,"assets/alternative_carte/do-nothing.jpg"));
    vec.push_back(std::make_unique<Carte>("teste",0,Faction::Neutre,"assets/alternative_carte/draw-and-discard.jpg"));
    Overlay overlay;
    int carteId = overlay.openOverlay("draw & discard",vec);
    if(carteId==vec[1]->getId()){
        joeur->piocher(1);
        joeur->defausserCarte(1);
    }
}