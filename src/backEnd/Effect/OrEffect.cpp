
#include "backEnd/Effect/OrEffect.hpp"
#include "backEnd/Carte/Carte.hpp"
#include "frontEnd/Overlay.hpp"
#include <string>
#include <vector>
/**
Le name doit etre le nom de la carte avec des - pour les espace 
sans majuscule
*/
OrEffect::OrEffect(std::string name, std::vector<IEffect> listeEffect):
        _name(name),
        _listeEffect(listeEffect)
        {};

void OrEffect::applyEffect(Joueur *joeur){

    std::string imagePath="assets/alternative_carte/"+_name;
    std::string imagePath1=imagePath+"/0.jpg";
    std::string imagePath2=imagePath+"/1.jpg";
    Carte carte1("teste",0,Faction::Neutre,imagePath1);
    Carte carte2("teste",0,Faction::Neutre,imagePath2);

    std::vector<Carte> vec;
    vec.push_back(carte1);
    vec.push_back(carte2);

    Overlay overlay;

    int carteID = overlay.openOverlay("teste",vec);

    if(carteID==carte1.getId()){
        _listeEffect[0].applyEffect(joeur);
    }
    else {
        _listeEffect[1].applyEffect(joeur);
    }
    
    
}

