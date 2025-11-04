#include "backEnd/Joueur.hpp"
#include "backEnd/Carte/Carte.hpp"
#include "backEnd/Carte/Champion.hpp"
#include "backEnd/Partie.hpp"
#include <climits>
#include <iostream>
#include <algorithm>
#include <tuple>
#include "frontEnd/Overlay.hpp"

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

// Non-const overload: retourne un pointeur modifiable vers la carte si trouvée
Carte* Joueur::getCarteById(int carteId) {
    for (auto& carte : _pioche) {
        if (carte->getId() == carteId) return carte.get();
    }
    for (auto& carte : _main) {
        if (carte->getId() == carteId) return carte.get();
    }
    for (auto& carte : _plateau) {
        if (carte->getId() == carteId) return carte.get();
    }
    for (auto& carte : _defausse) {
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
        case ZoneType::DefausseCommune: return _partie->getDefausseCommuneModifiable();
    }
    return _pioche; // Fallback
}

const std::vector<std::unique_ptr<Carte>>& Joueur::getZone(ZoneType type) const {
    switch (type) {
        case ZoneType::Pioche: return _pioche;
        case ZoneType::Main: return _main;
        case ZoneType::Plateau: return _plateau;
        case ZoneType::Defausse: return _defausse;
        case ZoneType::DefausseCommune: return _partie->getDefausseCommuneModifiable();
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
            auto rng = std::default_random_engine {};
            std::shuffle(std::begin(_defausse), std::end(_defausse), rng);
            _pioche = std::move(_defausse);
        }
        
        // Déplacer la dernière carte de la pioche vers la main
        _main.push_back(std::move(_pioche.back()));
        _pioche.pop_back();
    }
}
/**
    TO DO 
    implémenter l'event des diférente famile
*/
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

    effetfamille(carteJouee);
    
    std::cout << "Carte jouée avec succès" << std::endl;
    return true;
}

/*
isVert = false
1er carte verte : isVert non => autreVerte non => applique pas
2e carte verte : isVert non => autreVerte oui => applique sois même et la 1er carte
3e carte verte : isVert oui => applique sois même
fin de tour isVert = false
debut de tour : si plusieur carte verte : isVert = true et active vert des carte vertes 
*/
 
void Joueur::effetfamille(Carte* carteJouee) {
    // TO DO
    Faction faction = carteJouee->getFaction();
    auto etatinitial=_partie->getetatFaction();
    auto etat =_partie->getetatFaction()[faction];
    if(!std::get<0>(etat)){
        if(!std::get<1>(etat)){
            std::cout<<"applique pas"<<std::endl;
            
            etatinitial[faction]=std::make_tuple(false,true);
            _partie->setetatFaction(etatinitial);
            return;
        }
        else {
            //applique sois même et autre carte
            for(auto& carte : _plateau){
                if(carte->getFaction()==faction){
                    // aplique effect faction 
                    carte->jouerFaction(this);
                }
            }
            etatinitial[faction]=std::make_tuple(true,true);
            _partie->setetatFaction(etatinitial);
            return;
        }
    }
    else{
        // aplique sois même
        carteJouee->jouerFaction(this);
        return;
    }
}

bool Joueur::engagerCarte(int carteId){
    // Trouver la carte sur le plateau (vector<std::unique_ptr<Carte>>)
    auto it = trouverCarte(carteId, _plateau);
    if (it == _plateau.end()) {
        std::cerr << "Carte " << carteId << " non trouvée sur le plateau" << std::endl;
        return false;
    }

    // it est un iterator vers std::unique_ptr<Carte>
    Carte* carteJouee = it->get();

    if (!carteJouee) {
        std::cerr << "Erreur: pointeur de carte nul pour id=" << carteId << std::endl;
        return false;
    }
    if(carteJouee->jouerSacrifice(this)){
        deplacerCarte(carteId, ZoneType::Plateau,ZoneType::DefausseCommune);
        return true;
    }
    Champion* ch = dynamic_cast<Champion*>(carteJouee);
    if (!ch) {
        std::cerr << "La carte ciblée n'est pas un Champion" << std::endl;
        return false;
    }
    if(ch->getActiver()){
        std::cerr << "La carte ciblée est déjà engagée" << std::endl;
        return false;
    }
    ch->setActiver(true);
    std::cout << "Carte engagée: " << carteJouee->getName()
              << " (ID: " << carteJouee->getId() << ")" << std::endl;

    // Déclencher l'effet associé à l'engagement (ou autre logique)
    carteJouee->jouerEngager(this);  // IMPORTANT: passer 'this' (le joueur actuel)
    

    std::cout << "Carte engagée avec succès" << std::endl;
    return true;
}

void Joueur::defausserCarte(int carteId, ZoneType source) {
    deplacerCarte(carteId, source, ZoneType::Defausse);
}

void Joueur::defausserCarte(int count) {
    Overlay overlay;
    for(int i=0;i<count;i++){ 
        int carteId = overlay.openOverlay("DefausserCarte", _main);
        if (carteId == -1) {
            std::cerr << "Aucune carte sélectionnée pour la défausse." << std::endl;
            break; // Sortir si aucune carte n'est sélectionnée
        }
        defausserCarte(carteId, ZoneType::Main);
    }
}

void Joueur::defausserCarte() {
    // Move cards from hand to discard until the hand is empty.
    // Use deplacerCarte which removes from the source and adds to the destination.
    while (!_main.empty()) {
        int carteId = _main.back()->getId();
        // deplacerCarte will remove the card from _main and push it to _defausse
        deplacerCarte(carteId, ZoneType::Main, ZoneType::Defausse);
    }
    size_t i = 0;
    while (i < _plateau.size()) {
        Carte* c = _plateau[i].get();
        if (!c) {
            ++i;
            continue;
        }

        if (c->estChampion()) {
            // Conserver les champions sur le plateau
            Champion* ch = dynamic_cast<Champion*>(c);
            ch->setActiver(false); // Désengager le champion
            ++i;
        } else {
            int carteId = c->getId();
            // deplacerCarte retirera l'élément courant et le mettra en défausse.
            // Après l'appel, l'élément à l'indice 'i' est le suivant, on ne
            // doit donc pas incrémenter i dans ce cas.
            deplacerCarte(carteId, ZoneType::Plateau, ZoneType::Defausse);
        }
    }
}


void Joueur::initialiserDeck(std::vector<std::unique_ptr<Carte>> deck) {
    _pioche = std::move(deck);
    // Mélanger le deck ici si nécessaire
    std::random_device rd ;
    std::mt19937 g(rd());

    std::shuffle(_pioche.begin(), _pioche.end(), g);
}

void Joueur::melangerPioche() {
    if (_pioche.empty()) return;
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(_pioche.begin(), _pioche.end(), g);
}

bool Joueur::possedeGardien() const {
    for (const auto& carte : _plateau) {
        if (carte && carte->estChampion()) {
            Champion* champion = dynamic_cast<Champion*>(carte.get());
            if (champion && champion->getGardien()){
                return true;
            }
        }
    }
    return false;
}
bool Joueur::possedeChampion() const {
    for (const auto& carte : _plateau) {
        if (carte && carte->estChampion()) {
            return true;
        }
    }
    return false;
}

void Joueur::recevoirDegat(int montant) {
    _pv -= montant;
    if (_pv < 0) _pv = 0;
    std::cout << "Joueur " << _nom << " reçoit " << montant 
              << " dégâts. PV restants: " << _pv << std::endl;
}