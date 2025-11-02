#ifndef JOUEUR_HPP
#define JOUEUR_HPP

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <random>

class Carte;
class Partie;


enum class ZoneType {
    Pioche,
    Main,
    Plateau,
    Defausse,
    DefausseCommune
};

/**
 * Classe Joueur - Possède ses cartes via unique_ptr
 * Gestion claire de l'ownership et des transferts
 */
class Joueur {
private:
    int _id;
    int _pv;
    int _or;
    int _degat;
    int _compteurDefausse=0;
    std::string _nom;
    Partie* _partie;  // Non-owning pointer vers la partie
    
    // Les cartes sont POSSÉDÉES par le joueur
    std::vector<std::unique_ptr<Carte>> _pioche;
    std::vector<std::unique_ptr<Carte>> _main;
    std::vector<std::unique_ptr<Carte>> _plateau;
    std::vector<std::unique_ptr<Carte>> _defausse;

public:
    // Constructeur
    Joueur(int id, Partie* partie, const std::string& nom);
    
    // Destructeur
    ~Joueur();
    
    // Pas de copie (unique_ptr non copiable)
    Joueur(const Joueur&) = delete;
    Joueur& operator=(const Joueur&) = delete;
    
    // Move autorisé
    Joueur(Joueur&&) noexcept = default;
    Joueur& operator=(Joueur&&) noexcept = default;
    
    // === GETTERS ===
    int getId() const { return _id; };
    int getPv() const { return _pv; };
    int getOr() const { return _or; };
    int getDegat() const { return _degat; };
    std::string getNom() const { return _nom; };
    Partie* getPartie()  { return _partie; };
    int getCompteurDefausse() const {
        return _compteurDefausse;
    };
    
    // Accès en lecture seule aux zones (retourne des pointeurs non-owning)
    std::vector<const Carte*> getPioche() const;
    std::vector<const Carte*> getMain() const;
    std::vector<const Carte*> getPlateau() const;
    std::vector<const Carte*> getDefausse() const;
    
    // Accès par ID
    const Carte* getCarteById(int carteId) const;
    // mutable access (cherche dans les zones et retourne un pointeur modifiable)
    Carte* getCarteById(int carteId);
    
    // === SETTERS ===
    void setPv(int pv) { _pv = pv; }
    void setOr(int or_) { _or = or_; }
    void setDegat(int degat) {_degat = degat; }
    void ajouterDegat(int degat) { _degat += degat; }
    void retirerDegat(int degat) { _degat += degat; }
    void ajouterOr(int montant) { _or += montant; }
    void retirerOr(int montant) { _or -= montant; }
    void ajouterPV(int heal) { _pv += heal; }
    void retirerPV(int heal) { _pv -= heal; }
    void setCompteurDefausse(int count){ _compteurDefausse = count; };
    void addCompteurDefausse(int count){ _compteurDefausse += count; };
    
    // === GESTION DES CARTES ===
    
    /**
     * Ajoute une carte dans une zone spécifique
     * Prend possession de la carte
     */
    void ajouterCarte(std::unique_ptr<Carte> carte, ZoneType zone);
    
    /**
     * Retire une carte d'une zone par son ID
     * Transfère la propriété à l'appelant
     * @return unique_ptr vers la carte (nullptr si non trouvée)
     */
    std::unique_ptr<Carte> retirerCarte(int carteId, ZoneType zone);
    
    /**
     * Déplace une carte d'une zone à une autre
     * @return true si le déplacement a réussi
     */
    bool deplacerCarte(int carteId, ZoneType source, ZoneType destination);
    
    /**
     * Pioche n cartes de la pioche vers la main
     */
    void piocher(int nombre);
    
    /**
     * Joue une carte de la main vers le plateau
     * @return true si la carte a pu être jouée
     */
    bool jouerCarte(int carteId);

    /**
     * Gère les effets de famille lors du jeu d'une carte
     * TO DO: implémenter les effets spécifiques
     */
    void effetfamille(Carte* carteJouee);
    
    /**
    * Permet d'engager une carte et de faire son effet
    */
    bool engagerCarte(int carteID);
    /**
     * Défausse une carte depuis n'importe quelle zone
     */
    void defausserCarte(int carteId, ZoneType source);
    
    void defausserCarte(int count);
    /**
     * Crée le deck initial du joueur
     * Transfert de propriété depuis un vecteur externe
     */
    void initialiserDeck(std::vector<std::unique_ptr<Carte>> deck);

    /**
     * Mélange la pioche interne du joueur.
     */
    void melangerPioche();

    bool possedeGardien() const;

    // FIn de tour reset
    void resetAll(){
        _degat=0;
        _or=0;
    }

    void defausserCarte();
    
    void recevoirDegat(int montant);

    

private:
    // Méthodes helper
    std::vector<std::unique_ptr<Carte>>& getZone(ZoneType type);
    const std::vector<std::unique_ptr<Carte>>& getZone(ZoneType type) const;
    
    /**
     * Trouve une carte par ID dans une zone
     * @return Itérateur vers la carte (ou end() si non trouvée)
     */
    std::vector<std::unique_ptr<Carte>>::iterator 
        trouverCarte(int carteId, std::vector<std::unique_ptr<Carte>>& zone);
};

#endif // JOUEUR_HPP
