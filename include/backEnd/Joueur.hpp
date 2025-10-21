#ifndef JOUEUR_H
#define JOUEUR_H

#include "Carte/Carte.hpp"
#include "frontEnd/CarteGraphique.hpp"  // NOUVEAU
#include <list>
#include <vector>
#include <string>
#include <memory>  

class Partie;

class Joueur {
private:
    int _id;
    Partie& _partie;
    std::string _name;
    int _nbCarteCte;
    int _or;
    int _degat;
    int _pv;
    int _compteurDefausse=0;
    
    std::vector<Carte> _main;
    std::vector<Carte> _pioche;
    std::vector<Carte> _defausse;
    std::vector<Carte> _plateau;
    
    std::list<CarteGraphique> _cartesGraphiques;

public:
    Joueur();
    Joueur(int id, Partie& partie, const std::string name,std::vector<Carte> deck);
    ~Joueur();

    // Méthodes existantes
    void jouerUneCarte(Carte carte);
    void finDeTour();
    void activerUneCarte(Carte carte);
    void defausser(Carte carte);
    void piocher(int nbCarte);
    void melanger();
    void viderPlateau();
    void mouve(Carte& carte, std::vector<Carte>& source, std::vector<Carte>& destination);
    void mouve(std::vector<Carte>& source, std::vector<Carte>& destination);
    void mouve(Carte* carte, std::vector<Carte>& source, std::vector<Carte>& destination);
    void acheterUneCarte(Carte &carte);
    void attaque(Joueur jouer);
    
    // NOUVELLES méthodes pour la gestion graphique
    void creerCarteGraphique(Carte& carte, float x, float y);
    void dessinerCartes(sf::RenderWindow& window);
    void mettreAJourPositionsCartes();  // Pour réorganiser les cartes automatiquement
    void supprimerCarteGraphique(CarteGraphique* carte);
    // Getters
    inline int getId() const { return _id; }
    inline Partie& getPartie() const { return _partie; }  
    inline std::string getName() { return _name; }
    inline int getNbCarte() const { return _nbCarteCte; }
    int getPv() const { return _pv; }
    int getOr() const { return _or; }
    inline int getDegat() const { return _degat; }
    inline std::vector<Carte>& getMain()  { return _main; }
    inline std::vector<Carte> getPioche() const { return _pioche; }
    inline std::vector<Carte>& getDefausse()  { return _defausse; }
    inline std::vector<Carte>& getPlateau() { return _plateau; }
    auto& getCartesGraphiques() const { return _cartesGraphiques;}
    inline CarteGraphique* getCarteGraphiqueAtPosition(const sf::Vector2f& position) {
        for (auto& carteGraphique : _cartesGraphiques) {
            if (carteGraphique.contains(position)) {
                return &carteGraphique;  // Toujours valide !
            }
        }
        return nullptr;
    }
    // Setters
    inline void setId(int id) { _id = id; }
    //inline void setPartie(Partie &partie) { _partie = partie; }  
    inline void setName(std::string name) { _name = name; }
    inline void setNbCarte(int nbCarte) { _nbCarteCte = nbCarte; }
    inline void setOr(int ore) { _or = ore; }
    inline void setDegat(int degat) { _degat = degat; }
    inline void setPv(int pv) { _pv = pv; }
    inline void setMain(std::vector<Carte> main) { _main = main; }
    inline void setPioche(std::vector<Carte> pioche) { _pioche = pioche; }
    inline void setDefausse(std::vector<Carte> defausse) { _defausse = defausse; }
    inline void setPlateau(std::vector<Carte> plateau) { _plateau = plateau; }
};

#endif // JOUEUR_H