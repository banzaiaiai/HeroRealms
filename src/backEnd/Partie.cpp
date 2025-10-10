#include "backEnd/Partie.hpp"
#include "backEnd/Joueur.hpp"  // Inclure le header complet
#include <cstddef>


std::vector<Carte>* GLOBALRiviere = nullptr;
Joueur* GLOBALJoueurActif = nullptr;
Joueur* GLOBALJoueurCible = nullptr;
Carte* GLOBALCarteActif = nullptr;


Partie::Partie(int nbjoueur) : _tour(0) {
    // Créer les joueurs
    for (int i = 0; i < nbjoueur; ++i) {
        _listJoueur.push_back(new Joueur(i, *this, "Joueur " + std::to_string(i)));
    }
    _joueurActuelle = _listJoueur[0];




    // Initialisation dans un .cpp
    std::vector<Carte>* GLOBALRiviere = &_riviere;
    Joueur* GLOBALJoueurActif = _joueurActuelle;
    Joueur* GLOBALJoueurCible = nullptr;
    Carte* GLOBALCarteActif = nullptr;
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
