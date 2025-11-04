#include "backEnd/Partie.hpp"
#include "backEnd/Carte/Champion.hpp"
#include "backEnd/Joueur.hpp"
#include "backEnd/InitCarte.hpp"
#include "backEnd/Carte/Carte.hpp"
#include <iostream>
#include <algorithm>
#include <ostream>
#include <utility>

Joueur *GLOBALjoeurActuelle=nullptr;

Partie::Partie()
    : _joueurActuelIndex(0),
      _tour(1)
{
    std::cout << "Création d'une nouvelle partie" << std::endl;

    // Créer les joueurs
    Joueur joueur1(0, this, "Alice");
    Joueur joueur2(1, this, "Bob");
    
    // Initialiser les decks des joueurs (transfert de propriété)
    auto deck1= InitCarte::deckDeBase();
    auto deck2= InitCarte::deckDeBase();
    joueur1.initialiserDeck(std::move(deck1));
    joueur2.initialiserDeck(std::move(deck2));
    
    // Ajouter les joueurs à la partie
    ajouterJoueur(std::move(joueur1));
    ajouterJoueur(std::move(joueur2));

    // Piocher les mains de départ
    std::cout << "Pioche des mains de départ..." << std::endl;
    getJoueurParId(0)->piocher(5);


    // La Pioche
    _marcher = std::move(InitCarte::marcher()); 

    for (int i = 0; i < 5; i++) {
        ajouterCarteRiviere(std::move(_marcher.back()));
        _marcher.pop_back();
    }
    _defausseCommune.clear();
    _gemmeFeu=std::move(InitCarte::fireGems());
}

Partie::~Partie() {
    // Destruction automatique grâce aux smart pointers
    std::cout << "Destruction de la partie" << std::endl;
}

// === GESTION DES JOUEURS ===

void Partie::ajouterJoueur(Joueur&& joueur) {
    _joueurs.push_back(std::move(joueur));
    std::cout << "Joueur ajouté à la partie. Total: " << _joueurs.size() << std::endl;
    
}

Joueur* Partie::getJoueurActuelle() {
    if (_joueurs.empty()) return nullptr;
    return &_joueurs[_joueurActuelIndex];
}

const Joueur* Partie::getJoueurActuelle() const {
    if (_joueurs.empty()) return nullptr;
    return &_joueurs[_joueurActuelIndex];
}
Joueur * Partie::getAutreJoueurActuelle() {
    if (_joueurs.empty()) return nullptr;
    return &_joueurs[(_joueurActuelIndex + 1) % _joueurs.size()];
}
const Joueur* Partie::getAutreJoueurActuelle() const {
    if (_joueurs.empty()) return nullptr;
    return &_joueurs[(_joueurActuelIndex + 1) % _joueurs.size()];
}

Joueur* Partie::getJoueurParId(int id) {
    for (auto& joueur : _joueurs) {
        if (joueur.getId() == id) {
            return &joueur;
        }
    }
    return nullptr;
}

const Joueur* Partie::getJoueurParId(int id) const {
    for (const auto& joueur : _joueurs) {
        if (joueur.getId() == id) {
            return &joueur;
        }
    }
    return nullptr;
}

Joueur* Partie::getAutreJoueurParId(int id) {
    for (auto& joueur : _joueurs) {
        if (joueur.getId() != id) {
            return &joueur;
        }
    }
    return nullptr;
}
const Joueur* Partie::getAutreJoueurParId(int id) const {
    for (const auto& joueur : _joueurs) {
        if (joueur.getId() != id) {
            return &joueur;
        }
    }
    return nullptr;
}

void Partie::passerAuJoueurSuivant() {
    if (_joueurs.empty()) return;
    
    _joueurActuelIndex = (_joueurActuelIndex + 1) % _joueurs.size();
    
    if (_joueurActuelIndex == 0) {
        _tour++;
        std::cout << "=== Tour " << _tour << " ===" << std::endl;
    }
    
    std::cout << "C'est au tour de " << getJoueurActuelle()->getNom() << std::endl;

    GLOBALjoeurActuelle=getJoueurParId(_joueurActuelIndex);

    GLOBALjoeurActuelle->piocher(5);

    GLOBALjoeurActuelle->defausserCarte(GLOBALjoeurActuelle->getCompteurDefausse());
    GLOBALjoeurActuelle->setCompteurDefausse(0);
}

// === GESTION DE LA RIVIÈRE ===
std::vector<const Carte*> Partie::getRiviere() const {
    std::vector<const Carte*> result;
    result.reserve(_riviere.size());
    
    for (const auto& carte : _riviere) {
        result.push_back(carte.get());
    }
    
    return result;
}
std::vector<const Carte*> Partie::getMarcher() const {
    std::vector<const Carte*> result;
    result.reserve(_marcher.size());
    
    for (const auto& carte : _marcher) {
        result.push_back(carte.get());
    }
    
    return result;
}
std::vector<const Carte*> Partie::getGemmeFeu() const {
    std::vector<const Carte*> result;
    result.reserve(_gemmeFeu.size());
    
    for (const auto& carte : _gemmeFeu) {
        result.push_back(carte.get());
    }
    
    return result;
}
std::vector<const Carte*> Partie::getDefausseCommune() const {
    std::vector<const Carte*> result;
    result.reserve(_defausseCommune.size());
    
    for (const auto& carte : _defausseCommune) {
        result.push_back(carte.get());
    }
    
    return result;
}

void Partie::ajouterCarteRiviere(std::unique_ptr<Carte> carte) {
    if (!carte) return;
    
    _riviere.push_back(std::move(carte));
    std::cout << "Carte ajoutée à la rivière. Total: " << _riviere.size() << std::endl;
}


std::unique_ptr<Carte> Partie::retirerCarteRiviere(int carteId) {
    auto it = std::find_if(_riviere.begin(), _riviere.end(),
        [carteId](const std::unique_ptr<Carte>& carte) {
            return carte && carte->getId() == carteId;
        });
    
    if (it != _riviere.end()) {
        std::unique_ptr<Carte> carte = std::move(*it);
        _riviere.erase(it);
        std::cout << "Carte " << carteId << " retirée de la rivière" << std::endl;

        if (!_marcher.empty()) {
            // Replace the removed river card with the last card from the marcher
            ajouterCarteRiviere(std::move(_marcher.back()));
            _marcher.pop_back();
        } else {
            // Defensive: avoid calling back() on an empty vector
            std::cerr << "Attention: le marcher est vide, impossible de remplacer la carte retirée" << std::endl;
        }

        return carte;
    }
    
    std::cerr << "Carte " << carteId << " non trouvée dans la rivière" << std::endl;
    return nullptr;
}

std::unique_ptr<Carte> Partie::retirerCarteMarcher(int carteId) {
    auto it = std::find_if(_marcher.begin(), _marcher.end(),
        [carteId](const std::unique_ptr<Carte>& carte) {
            return carte && carte->getId() == carteId;
        });
    
    if (it != _marcher.end()) {
        std::unique_ptr<Carte> carte = std::move(*it);
        _marcher.erase(it);
        std::cout << "Carte " << carteId << " retirée de la rivière" << std::endl;
        return carte;
    }
    std::cerr << "Carte " << carteId << " non trouvée dans la rivière" << std::endl;
    return nullptr;
}

std::unique_ptr<Carte> Partie::retirerGemmeFeu(int carteId) {
    auto it = std::find_if(_gemmeFeu.begin(), _gemmeFeu.end(),
        [carteId](const std::unique_ptr<Carte>& carte) {
            return carte && carte->getId() == carteId;
        });

    if (it != _gemmeFeu.end()) {
        std::unique_ptr<Carte> carte = std::move(*it);
        _gemmeFeu.erase(it);
        std::cout << "Gemme feu " << carte->getId() << " retirée" << std::endl;
        return carte;
    }

    std::cerr << "Gemme feu id " << carteId << " introuvable" << std::endl;
    return nullptr;
}

void Partie::remplirRiviere() {
    // Cette méthode pourrait piocher depuis un deck commun
    // Pour l'instant, c'est juste un placeholder
    std::cout << "Remplissage de la rivière (à implémenter)" << std::endl;
}

void Partie::setMarcher(std::vector<std::unique_ptr<Carte>> marcher) {
    _marcher = std::move(marcher);
}

// === GESTION DU JEU ===

void Partie::demarrer() {
    if(!_joueurs.empty()){
        GLOBALjoeurActuelle=getJoueurParId(0);
        std::cout<<getJoueurParId(0)<<"joueur actuelle"<<std::endl;
    }
    std::cout << "=== Début de la partie ===" << std::endl;
    std::cout << "Nombre de joueurs: " << _joueurs.size() << std::endl;
    
    if (!_joueurs.empty()) {
        std::cout << "Premier joueur: " << getJoueurActuelle()->getNom() << std::endl;
    }
}

void Partie::finDeTour() {
    std::cout << "Fin du tour de " << getJoueurActuelle()->getNom() << std::endl;
    
    // Logique de fin de tour (défausser la main, piocher, etc.)
    Joueur* joueur = getJoueurActuelle();
    if (joueur) {
        // Exemple: remettre l'or à une valeur de base
        joueur->setOr(joueur->getOr() + 1);
        
        // Piocher des cartes si la main est vide
        if (joueur->getMain().empty()) {
            joueur->piocher(5);
        }
    }
    
    passerAuJoueurSuivant();
}
/**
    Attaque une carte avec son id

*/
bool Partie::attaque(int idCarteSelect){
    Joueur* joueurActuelle=getJoueurActuelle();
    Joueur* autreJoueur=getAutreJoueurActuelle();
    if(!joueurActuelle || !autreJoueur){
        std::cerr<<"Probléme de joueur dans l'attaque"<<std::endl;
        return false;
    }
    // Chercher la carte cible (mutable) dans le plateau de l'autre joueur
    Carte* carteModifiable = autreJoueur->getCarteById(idCarteSelect);
    if (!carteModifiable) {
        std::cerr << "Probléme de carte dans l'attaque: id introuvable sur le plateau adversaire" << std::endl;
        return false;
    }

    // Vérifier que la carte est un Champion via dynamic_cast
    Champion* cartecible = dynamic_cast<Champion*>(carteModifiable);
    if (!cartecible) {
        std::cerr << "La carte ciblée n'est pas un Champion" << std::endl;
        return false;
    }

    int degat = joueurActuelle->getDegat();
    if(!autreJoueur->possedeGardien() || cartecible->getGardien()){
        joueurActuelle->setDegat(degat-cartecible->getPvTotal()); // Réinitialiser les dégâts après l'attaque
        cartecible->recevoirDegat(degat);
        if(cartecible->getPvTotal()<=0){
            std::cout << cartecible->getName() << " est détruit!" << std::endl;
            // Déplacer la carte vers la défausse de l'autre joueur
            if(!autreJoueur->deplacerCarte(idCarteSelect, ZoneType::Plateau, ZoneType::Defausse)){
                std::cerr<<"Erreur lors du déplacement de la carte détruite vers la défausse"<<std::endl;
            }
        }
        std::cout << cartecible->getName() << " a reçu " << degat << " dégats." << std::endl;
    }
    else {
        std::cout<<"Le joueur posséde un gariden, vous ataquer une carte qui n'est pas gardient"<<std::endl;
        return false;
    }
    
    return true;
}


/**
Prend un vectteur de carte et le mélange */

void Partie::melangerCartes(std::vector<const Carte*>& cartes) {
    std::random_device rd;
    std::mt19937 g(rd());
    if (cartes.empty()) return;
    std::shuffle(cartes.begin(), cartes.end(), g);
}
