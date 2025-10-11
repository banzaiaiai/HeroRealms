#include "backEnd/Partie.hpp"
#include "backEnd/Carte/Carte.hpp"
#include "backEnd/Joueur.hpp"  // Inclure le header complet
#include <cstddef>
#include <vector>


std::vector<Carte>* GLOBALRiviere = nullptr;
Joueur* GLOBALJoueurActif = nullptr;
Joueur* GLOBALJoueurCible = nullptr;
Carte* GLOBALCarteActif = nullptr;


Partie::Partie(std::vector<Carte> deck,int nbjoueur) : _tour(0) {
    // Créer les joueurs
    for (int i = 0; i < nbjoueur; ++i) {
        _listJoueur.push_back( Joueur(i, *this, "Joueur " + std::to_string(i),deck));
    }
    setJoueurActuelle(_listJoueur[0]);




    // Initialisation dans un .cpp
    std::vector<Carte>* GLOBALRiviere = _riviere;
    Joueur* GLOBALJoueurActif = _joueurActuelle;
    Joueur* GLOBALJoueurCible = nullptr;
    Carte* GLOBALCarteActif = nullptr;
}

Partie::~Partie() {
    
}

// Implémentation des méthodes de fonctionement
bool Partie::victoireDefaite(Joueur* joueur)
{
  if(joueur->getPv()==0){
    return true ;
  }
  return false;
}