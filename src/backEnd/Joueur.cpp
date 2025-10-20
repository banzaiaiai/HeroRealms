#include "backEnd/Joueur.hpp"
#include "backEnd/Carte/Carte.hpp"
#include "backEnd/Partie.hpp"  // Inclure le header complet
#include "backEnd/Carte/NonPermanent.hpp"
#include <iostream>
#include <iterator>
#include <list>
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
// NOUVELLES méthodes graphiques
void Joueur::creerCarteGraphique(Carte& carte, float x, float y) {
        _cartesGraphiques.emplace_back(x, y, 80.f, 120.f, &carte);
        carte.setCarteGraphique(&_cartesGraphiques.back());  // Adresse stable !
}

void Joueur::dessinerCartes(sf::RenderWindow& window) {
        for (auto& carteGraphique : _cartesGraphiques) {
            carteGraphique.draw(window);
        }
}

// Méthode pour supprimer une carte graphique si besoin
void Joueur::supprimerCarteGraphique(CarteGraphique* carte) {
    _cartesGraphiques.remove_if([carte](const CarteGraphique& c) {
        return &c == carte;
    });
}


void Joueur::mettreAJourPositionsCartes() {
    // Réorganise les cartes de la main
    float startX = 50.f;
    float y = 400.f;
    float espacement = 90.f;
    
    int index = 0;
    for (auto& carteGraphique : _cartesGraphiques) {
        // Trouver la carte logique associée
        Carte* carteLogique = carteGraphique.getCarteLogique();
        
        // Vérifier si la carte est dans la main
        if (carteLogique && std::find(_main.begin(), _main.end(), *carteLogique) != _main.end()) {
            carteGraphique.setPosition(startX + index * espacement, y);
            index++;
        }
    }
}