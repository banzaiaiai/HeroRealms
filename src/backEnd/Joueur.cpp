#include "backEnd/Joueur.hpp"
#include "backEnd/Partie.hpp"  // Inclure le header complet

Joueur::Joueur() : _id(0), _partie(nullptr), _name(""), _nbCarte(0), _or(0), _degat(0), _pv(50) {}

Joueur::Joueur(int id, Partie* partie, std::string name) 
    : _id(id), _partie(partie), _name(name), _nbCarte(0), _or(0), _degat(0), _pv(50) {}

Joueur::~Joueur() {
    // Libérer la mémoire si nécessaire
}

// Implémentation des autres méthodes...
