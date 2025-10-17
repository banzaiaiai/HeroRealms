#include "backEnd/Joueur.hpp"
#include "backEnd/Carte/Carte.hpp"
#include "backEnd/Partie.hpp"  // Inclure le header complet
#include <random>
#include <typeinfo>
#include <vector>
#include <algorithm>

Joueur::Joueur(int id, Partie& partie, std::string name,std::vector<Carte> deck) 
    : _id(id), _partie(partie), _name(name), _nbCarteCte(5), _or(0), _degat(0), _pv(50),_pioche(deck){
    _main.clear();
    _defausse.clear();
    _plateau.clear();
    
    // Piocher les cartes initiales
    
    melanger();
    piocher(_nbCarteCte);
}

Joueur::~Joueur() {
    // Libérer la mémoire si nécessaire
}

// Implémentation des méthode de fonctionnement 

void Joueur::piocher(int nbCarte){
    for (int i=0; i<nbCarte ; i++){
        // Si la pioche est vide la remélange
        if(_pioche.empty()){
           melanger(); 
        }
        mouve(_pioche, _main);
    }
}

void Joueur::finDeTour(){
    // vide la main 
    for (Carte carte : _main){
        mouve(carte,_main,_defausse);
    }
    // vide les caractéristique du joueur
    setDegat(0);
    setOr(0);

    // repioche la main
    piocher(_nbCarteCte);
    
    viderPlateau();
}

void Joueur::melanger(){
    for(Carte carte : _defausse){
        mouve(carte,_defausse,_pioche);
    }
    std::random_device rd ;
    std::mt19937 g(rd());

    std::shuffle(_pioche.begin(), _pioche.end(), g);
}

// CORRECTION : Méthodes de déplacement
void Joueur::mouve(std::vector<Carte>& source, std::vector<Carte>& destination) {
    if (!source.empty()) {
        destination.push_back(source.back());
        source.pop_back();
    }
}

void Joueur::mouve(Carte& carte, std::vector<Carte>& source, std::vector<Carte>& destination) {
    // Recherche de la carte dans le vecteur source
    auto it = std::find(source.begin(), source.end(), carte);
    if (it != source.end()) {
        destination.push_back(*it);
        source.erase(it);
    }
}



void Joueur::viderPlateau(){
    for(Carte carte : _plateau) {
        if (typeid(carte)==typeid(NonPermanent)) // faux le changer pour les non permanent
        {
            mouve(carte,_plateau,_defausse);
        }
    }
}

void Joueur::jouerUneCarte(Carte carte){
    mouve(carte,_main,_plateau);
    GLOBALJoueurActif=this;
    GLOBALCarteActif=&carte;
}

void Joueur::defausser(Carte carte){
    mouve(carte,_main,_defausse);
}

void Joueur::acheterUneCarte(Carte & carte){
    if(carte.getCoupOr()>=this->getOr()){
        this->setOr(this->getOr()-carte.getCoupOr());
        mouve(carte,_partie.getRiviere(),_defausse);
    }
}

// Il faut compléter & changer. Uniquement fait pour la phase de test
void Joueur::attaque(Joueur joueur){
    joueur.setPv(joueur.getPv()-this->getDegat());
}