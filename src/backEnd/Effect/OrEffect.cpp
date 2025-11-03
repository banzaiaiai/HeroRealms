
#include "backEnd/Effect/OrEffect.hpp"
#include "backEnd/Carte/Carte.hpp"
#include "frontEnd/Overlay.hpp"
#include <string>
#include <vector>
#include <memory>
/**
Le name doit etre le nom de la carte avec des - pour les espace 
sans majuscule
*/
OrEffect::OrEffect(const std::string& name, const std::vector<std::shared_ptr<IEffect>>& listeEffect)
    : _name(name), _listeEffect(listeEffect) {}

void OrEffect::applyEffect(Joueur *joeur){

    std::string imagePath="assets/alternative_carte/"+_name;
    std::string imagePath1=imagePath+"/0.jpg";
    std::string imagePath2=imagePath+"/1.jpg";
    // Build two heap-allocated Carte instances and pass them as a vector
    // of unique_ptr so the Overlay templated overload can extract raw pointers.
    std::vector<std::unique_ptr<Carte>> vec;
    vec.push_back(std::make_unique<Carte>("teste", 0, Faction::Neutre, imagePath1));
    vec.push_back(std::make_unique<Carte>("teste", 0, Faction::Neutre, imagePath2));

    Overlay overlay;

    int carteID = overlay.openOverlay("teste", vec);

    if (carteID == vec[0]->getId()) {
        _listeEffect[0]->applyEffect(joeur);
    } else {
        _listeEffect[1]->applyEffect(joeur);
    }
    
    
}

