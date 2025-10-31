#include "backEnd/Carte/Carte.hpp"
#include "backEnd/Joueur.hpp"
#include "backEnd/Partie.hpp"
#include "backEnd/Effect/IEffect.hpp"
#include <iostream>
#include <ostream>

// Initialisation du compteur d'IDs
int Carte::_nextId = 0;

Carte::Carte() 
    : _id(_nextId++),
      _name("Carte sans nom"),
      _coupOr(0),
      _faction(Faction::Neutre)
{
    std::cout << "Creation carte par defaut" << std::endl;    
}

Carte::Carte(const std::string& name, int coupOr, Faction faction, std::string imagePath)
    : _id(_nextId++),
      _name(name),
      _coupOr(coupOr),
      _faction(faction)
{
    if (!_texture.loadFromFile(imagePath)) {
        std::cerr << "Erreur : impossible de charger l'image " << imagePath << std::endl;
    }
}

Carte::~Carte() {
    std::cout << "Destruction de la carte: " << _name <<" "<< this<< " "<< _id << std::endl;
}

// Move constructor
Carte::Carte(Carte&& other) noexcept
    : _id(other._id),
      _name(std::move(other._name)),
      _coupOr(other._coupOr),
      _faction(other._faction),
      _trigger(std::move(other._trigger))
{
}

// Move assignment
Carte& Carte::operator=(Carte&& other) noexcept {
    if (this != &other) {
        _id = other._id;
        _name = std::move(other._name);
        _coupOr = other._coupOr;
        _faction = other._faction;
        _trigger = std::move(other._trigger);
    }
    return *this;
}

void Carte::addTrigger(EventType eventType, std::vector<std::shared_ptr<IEffect>> effects) {
    _trigger[eventType] = std::move(effects);
}

const std::vector<std::shared_ptr<IEffect>>* Carte::getEffects(EventType eventType) const {
    auto it = _trigger.find(eventType);
    if (it != _trigger.end()) {
        return &(it->second);
    }
    return nullptr;
}

void Carte::jouer(Joueur* joueur)
{
    std::cout << "Carte '" << _name << "' jouée par " << joueur->getNom() << std::endl;
    declencherEffets(EventType::OnPlay, joueur);
}

void Carte::jouerFaction(Joueur* joueur)
{
    std::cout << "Carte '" << _name << "' jouée par " << joueur->getNom() << std::endl;
    declencherEffets(EventType::OnAllyEnter, joueur);
}

void Carte::jouerEngager(Joueur* joueur)
{
    std::cout << "Carte '" << _name << "' jouée par " << joueur->getNom() << std::endl;
    declencherEffets(EventType::OnEngage, joueur);
}

void Carte::declencherEffets(EventType eventType, Joueur* joueur) {
    if (!joueur) {
        std::cerr << "Erreur: joueur nullptr dans declencherEffets" << std::endl;
        return;
    }
    
    auto it = _trigger.find(eventType);
    if (it != _trigger.end()) {
        std::cout << "Déclenchement de " << it->second.size() 
                  << " effet(s) pour la carte " << _name << std::endl;
        
        for (const auto& effect : it->second) {
            if (effect) {
                effect->applyEffect(joueur);
            } else {
                std::cerr << "Effet nullptr trouvé!" << std::endl;
            }
        }
    } else {
        std::cout << "Aucun effet trouvé pour cet événement" << std::endl;
    }
}

