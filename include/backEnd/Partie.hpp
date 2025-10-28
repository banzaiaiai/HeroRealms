#ifndef PARTIE_HPP
#define PARTIE_HPP

#include <vector>
#include <memory>

class Carte;
class Joueur;

/**
 * Classe Partie - Gère l'état global du jeu
 * Possède la rivière (marché) et coordonne les joueurs
 */
class Partie {
private:
    std::vector<Joueur> _joueurs;
    std::vector<std::unique_ptr<Carte>> _riviere;  // Le marché commun
    int _joueurActuelIndex;
    int _tour;

public:
    Partie();
    ~Partie();
    
    // Pas de copie
    Partie(const Partie&) = delete;
    Partie& operator=(const Partie&) = delete;
    
    // === GESTION DES JOUEURS ===
    
    /**
     * Ajoute un joueur à la partie
     */
    void ajouterJoueur(Joueur&& joueur);
    
    /**
     * Retourne le joueur actuel (celui qui joue)
     */
    Joueur* getJoueurActuelle();
    const Joueur* getJoueurActuelle() const;
    
    /**
     * Retourne un joueur par son ID
     */
    Joueur* getJoueurParId(int id);
    const Joueur* getJoueurParId(int id) const;
    
    /**
     * Retourne la liste de tous les joueurs
     */
    std::vector<Joueur>& getListJoueur() { return _joueurs; }
    const std::vector<Joueur>& getListJoueur() const { return _joueurs; }
    
    /**
     * Passe au joueur suivant
     */
    void passerAuJoueurSuivant();
    
    // === GESTION DE LA RIVIÈRE (MARCHÉ) ===
    
    /**
     * Retourne les cartes de la rivière (lecture seule)
     */
    std::vector<const Carte*> getRiviere() const;
    
    /**
     * Ajoute une carte à la rivière
     */
    void ajouterCarteRiviere(std::unique_ptr<Carte> carte);
    
    /**
     * Retire une carte de la rivière par son ID
     * Transfère la propriété à l'appelant
     */
    std::unique_ptr<Carte> retirerCarteRiviere(int carteId);
    
    /**
     * Remplit la rivière jusqu'à avoir N cartes
     */
    void remplirRiviere(int nombreCartes);
    
    // === GESTION DU JEU ===
    
    /**
     * Démarre la partie
     */
    void demarrer();
    
    /**
     * Termine le tour actuel
     */
    void finDeTour();
    
    /**
     * Retourne le numéro du tour actuel
     */
    int getTour() const { return _tour; }
};

#endif // PARTIE_HPP