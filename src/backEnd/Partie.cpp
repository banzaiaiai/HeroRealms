#include "backEnd/Partie.hpp"
#include "backEnd/Joueur.hpp"  // Inclure le header complet

Partie::Partie(int nbjoueur) : _tour(0) {
    // Créer les joueurs
    for (int i = 0; i < nbjoueur; ++i) {
        _listJoueur.push_back(new Joueur(i, this, "Joueur " + std::to_string(i)));
    }
    _joueurActuelle = _listJoueur[0];
}

Partie::~Partie() {
    // Libérer la mémoire des joueurs
    for (auto* joueur : _listJoueur) {
        delete joueur;
    }
}

bool Partie::victoireDefaite(Joueur* joueur)
{
  if(joueur->getPv()==0){
    return true ;
  }
  return false;
}
// Implémentation des autres méthodes...
