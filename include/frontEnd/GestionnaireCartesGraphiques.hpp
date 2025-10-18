#ifndef GESTIONNAIRECARTESGRAPHIQUES_HPP
#define GESTIONNAIRECARTESGRAPHIQUES_HPP

#include "frontEnd/CarteGraphique.hpp"

class GestionnaireCartesGraphiques {
private:
    std::vector<CarteGraphique> _cartesGraphiques;
    std::map<Carte*, CarteGraphique*> _liaisonLogiqueGraphique;
    
public:
    CarteGraphique* creerCarteGraphique(Carte* carteLogique, float x, float y) {
        _cartesGraphiques.emplace_back(x, y, 80.f, 120.f, carteLogique);
        CarteGraphique* nouvelleCarte = &_cartesGraphiques.back();
        _liaisonLogiqueGraphique[carteLogique] = nouvelleCarte;
        return nouvelleCarte;
    }
    
    CarteGraphique* getCarteGraphique(Carte* carteLogique) {
        auto it = _liaisonLogiqueGraphique.find(carteLogique);
        return (it != _liaisonLogiqueGraphique.end()) ? it->second : nullptr;
    }
    
    Carte* getCarteLogique(CarteGraphique* carteGraphique) {
        return carteGraphique->getCarteLogique();
    }
};

#endif