#ifndef PARTIE_H
#define PARTIE_H

#include "backEnd/Carte/Carte.hpp"
#include <vector>
#include <memory>

// Forward declaration
class Joueur;

class Partie {
private:
    std::vector<Joueur*> _listJoueur;  // POINTEURS au lieu d'objets
    std::vector<Carte> _riviere;
    std::vector<Carte> _marche;
    Joueur* _joueurActuelle;  // POINTEUR
    int _tour = 0;

public:
    Partie(int nbjoueur = 2);
    ~Partie();  // N'oubliez pas le destructeur pour gérer la mémoire
    
    bool victoireDefaite(Joueur* joueur);  // Prend un pointeur
    void consulterDefausse(Joueur* joueur, bool sacrifice);  // Prend un pointeur
    void acheterUneCarte(Carte carte);

    // Getters
    inline std::vector<Joueur*>& getListJoueur() { return _listJoueur; }  // Retourne des pointeurs
    inline std::vector<Carte> getRiviere() const { return _riviere; }
    inline std::vector<Carte> getMarche() const { return _marche; }
    inline Joueur* getJoueurActuelle() const { return _joueurActuelle; }  // Retourne un pointeur
    inline int getTour() const { return _tour; }

    // Setters
    inline void setRiviere(std::vector<Carte> riviere) { _riviere = riviere; }
    inline void setMarche(std::vector<Carte> marche) { _marche = marche; }
    inline void setJoueurActuelle(Joueur* joueurActuelle) { _joueurActuelle = joueurActuelle; }  // Prend un pointeur
    inline void setTour(int tour) { _tour = tour; }
};

#endif // PARTIE_H
