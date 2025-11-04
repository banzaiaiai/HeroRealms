#ifndef PARTIE_HPP
#define PARTIE_HPP

#include "backEnd/Carte/Carte.hpp"
#include <map>
#include <tuple>
#include <vector>
#include <memory>

class Carte;
class Joueur;
class Overlay;

extern Joueur* GLOBALjoeurActuelle;
/**
 * Classe Partie - Gère l'état global du jeu
 * Possède la rivière (marché) et coordonne les joueurs
 */
class Partie {
private:
    std::vector<Joueur> _joueurs;
    std::vector<std::unique_ptr<Carte>> _riviere;  // Le marché commun
    std::vector<std::unique_ptr<Carte>> _marcher;
    std::vector<std::unique_ptr<Carte>> _defausseCommune;
    std::vector<std::unique_ptr<Carte>> _gemmeFeu;
    int _joueurActuelIndex;
    int _tour;
    std::map<Faction,std::tuple<bool,bool>> _etatFaction;

public:
    Overlay* overlay = nullptr;
    void setOverlay(Overlay* o) { overlay = o; };

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
     * Retourne l'autre joueur (celui qui ne joue pas)
     */
    Joueur * getAutreJoueurActuelle();
    const Joueur* getAutreJoueurActuelle() const;
    /**
     * Retourne un joueur par son ID
     */
    Joueur* getJoueurParId(int id);
    const Joueur* getJoueurParId(int id) const;
    
    /**
     * Retourne l'autre joueur par son ID
     */
    Joueur* getAutreJoueurParId(int id);
    const Joueur* getAutreJoueurParId(int id) const;
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
     * Retourne les cartes du marcher (lecture seule)
     */
    std::vector<const Carte*> getMarcher() const;
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
     * Retire une carte de la pile de gemmes feu par ID.
     * Transfère la propriété à l'appelant.
     */
    std::unique_ptr<Carte> retirerGemmeFeu(int carteId);
    /**
     * Retire une carte de la pile du marcher par ID.
     * Transfère la propriété à l'appelant.
     */
    std::unique_ptr<Carte> retirerCarteMarcher(int carteId);
    /**
     * Remplit la rivière jusqu'à avoir N cartes
     */
    void remplirRiviere();
    void setMarcher(std::vector<std::unique_ptr<Carte>> marcher);
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

    std::map<Faction,std::tuple<bool,bool>> getetatFaction(){ return _etatFaction; };
    void setetatFaction(std::map<Faction,std::tuple<bool,bool>> etatfaction){ _etatFaction=etatfaction; };
    void resetetatFaction(){
        for(auto& pair : _etatFaction){
            pair.second=std::make_tuple(false,false);
        }
    }

    // Gestion de l'attaque
    
    bool attaque(int idCarteSelect);

    // Mélange un vecteur de pointeurs vers Carte (utile pour shuffle des vues)
    void melangerCartes(std::vector<const Carte*>& cartes);


    void setGemmeFeu(std::vector<std::unique_ptr<Carte>> gemmeFeu);
    std::vector<const Carte*> getGemmeFeu() const;

    void setDefausseCommune(std::vector<std::unique_ptr<Carte>> defausseCommune);
    std::vector<const Carte*> getDefausseCommune() const;

    std::vector<std::unique_ptr<Carte>>& getDefausseCommuneModifiable()
    {return _defausseCommune;};
};

#endif // PARTIE_HPP
