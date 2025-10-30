#include "backEnd/Joueur.hpp"
#include "backEnd/Carte/Carte.hpp"
#include "backEnd/Partie.hpp"
#include <iostream>
#include <algorithm>

Joueur::Joueur(int id, Partie* partie, const std::string& nom)
    : _id(id),
      _pv(20),
      _or(0),
      _degat(0),
      _nom(nom),
      _partie(partie)

{
    std::cout << "Joueur " << _nom << " créé avec ID " << _id << std::endl;
}

Joueur::~Joueur() {
    // Les unique_ptr se détruisent automatiquement
    std::cout << "Joueur " << _nom << " détruit avec ID " << _id << std::endl;
}

// === ACCÈS EN LECTURE SEULE ===

std::vector<const Carte*> Joueur::getPioche() const {
    std::vector<const Carte*> result;
    result.reserve(_pioche.size());
    for (const auto& carte : _pioche) {
        result.push_back(carte.get());
    }
    return result;
}

std::vector<const Carte*> Joueur::getMain() const {
    std::vector<const Carte*> result;
    result.reserve(_main.size());
    for (const auto& carte : _main) {
        result.push_back(carte.get());
    }
    return result;
}

std::vector<const Carte*> Joueur::getPlateau() const {
    std::vector<const Carte*> result;
    result.reserve(_plateau.size());
    for (const auto& carte : _plateau) {
        result.push_back(carte.get());
    }
    return result;
}

std::vector<const Carte*> Joueur::getDefausse() const {
    std::vector<const Carte*> result;
    result.reserve(_defausse.size());
    for (const auto& carte : _defausse) {
        result.push_back(carte.get());
    }
    return result;
}

const Carte* Joueur::getCarteById(int carteId) const {
    // Chercher dans toutes les zones
    for (const auto& carte : _pioche) {
        if (carte->getId() == carteId) return carte.get();
    }
    for (const auto& carte : _main) {
        if (carte->getId() == carteId) return carte.get();
    }
    for (const auto& carte : _plateau) {
        if (carte->getId() == carteId) return carte.get();
    }
    for (const auto& carte : _defausse) {
        if (carte->getId() == carteId) return carte.get();
    }
    return nullptr;
}

// === HELPERS PRIVÉS ===

std::vector<std::unique_ptr<Carte>>& Joueur::getZone(ZoneType type) {
    switch (type) {
        case ZoneType::Pioche: return _pioche;
        case ZoneType::Main: return _main;
        case ZoneType::Plateau: return _plateau;
        case ZoneType::Defausse: return _defausse;
    }
    return _pioche; // Fallback
}

const std::vector<std::unique_ptr<Carte>>& Joueur::getZone(ZoneType type) const {
    switch (type) {
        case ZoneType::Pioche: return _pioche;
        case ZoneType::Main: return _main;
        case ZoneType::Plateau: return _plateau;
        case ZoneType::Defausse: return _defausse;
    }
    return _pioche; // Fallback
}

std::vector<std::unique_ptr<Carte>>::iterator 
Joueur::trouverCarte(int carteId, std::vector<std::unique_ptr<Carte>>& zone) {
    return std::find_if(zone.begin(), zone.end(),
        [carteId](const std::unique_ptr<Carte>& carte) {
            return carte && carte->getId() == carteId;
        });
}

// === GESTION DES CARTES ===

void Joueur::ajouterCarte(std::unique_ptr<Carte> carte, ZoneType zone) {
    if (!carte) return;
    getZone(zone).push_back(std::move(carte));
}

std::unique_ptr<Carte> Joueur::retirerCarte(int carteId, ZoneType zone) {
    auto& zoneRef = getZone(zone);
    auto it = trouverCarte(carteId, zoneRef);
    
    if (it != zoneRef.end()) {
        // Extraction de la carte
        std::unique_ptr<Carte> carte = std::move(*it);
        zoneRef.erase(it);
        return carte;
    }
    
    return nullptr; // Carte non trouvée
}

bool Joueur::deplacerCarte(int carteId, ZoneType source, ZoneType destination) {
    // Validation
    if (source == destination) return false;
    
    // Retirer de la zone source
    auto carte = retirerCarte(carteId, source);
    if (!carte) {
        std::cerr << "Carte " << carteId << " non trouvée dans la zone source" << std::endl;
        return false;
    }
    
    // Ajouter à la zone destination
    ajouterCarte(std::move(carte), destination);
    
    std::cout << "Carte " << carteId << " déplacée avec succès" << std::endl;
    return true;
}

void Joueur::piocher(int nombre) {
    for (int i = 0; i < nombre; i++) {
        if (_pioche.empty()) {
            std::cout << "Pioche vide, impossible de piocher" << std::endl;
            break;
            /* To Do 
            Ajouter la logique de remélange de la défausse dans la pioche ici
            */
        }
        
        // Déplacer la dernière carte de la pioche vers la main
        _main.push_back(std::move(_pioche.back()));
        _pioche.pop_back();
    }
}

bool Joueur::jouerCarte(int carteId) {
    // Trouver la carte dans la main
    auto it = trouverCarte(carteId, _main);
    if (it == _main.end()) {
        std::cerr << "Carte " << carteId << " non trouvée dans la main" << std::endl;
        return false;
    }
    // Déplacer vers le plateau
    _plateau.push_back(std::move(*it));
    _main.erase(it);

    // La carte est maintenant sur le plateau (dernière carte ajoutée)
    Carte* carteJouee = _plateau.back().get();
    
    if (carteJouee) {
        std::cout << "Carte jouée: " << carteJouee->getName() 
                  << " (ID: " << carteJouee->getId() << ")" << std::endl;
        
        // Déclencher l'effet OnPlay
        carteJouee->jouer(this);  // IMPORTANT: passer 'this' (le joueur actuel)
    }
    
    std::cout << "Carte jouée avec succès" << std::endl;
    return true;
    return true;
}

 



void Joueur::defausserCarte(int carteId, ZoneType source) {
    deplacerCarte(carteId, source, ZoneType::Defausse);
}

void Joueur::initialiserDeck(std::vector<std::unique_ptr<Carte>> deck) {
    _pioche = std::move(deck);
    // Mélanger le deck ici si nécessaire
    std::random_device rd ;
    std::mt19937 g(rd());

    std::shuffle(_pioche.begin(), _pioche.end(), g);
}

/* 
Achat de carte
// Vérifier le coût
    if (_or < (*it)->getCoupOr()) {
        std::cerr << "Pas assez d'or pour jouer cette carte" << std::endl;
        return false;
    }
    
    // Payer le coût
    _or -= (*it)->getCoupOr();
*/
