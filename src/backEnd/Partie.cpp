#include "backEnd/Partie.hpp"
#include "backEnd/Joueur.hpp"
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

void Partie::passerAuJoueurSuivant() {
    if (_joueurs.empty()) return;
    
    _joueurActuelIndex = (_joueurActuelIndex + 1) % _joueurs.size();
    
    if (_joueurActuelIndex == 0) {
        _tour++;
        std::cout << "=== Tour " << _tour << " ===" << std::endl;
    }
    
    std::cout << "C'est au tour de " << getJoueurActuelle()->getNom() << std::endl;

    GLOBALjoeurActuelle=getJoueurParId(_joueurActuelIndex);
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

void Partie::remplirRiviere(int nombreCartes) {
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