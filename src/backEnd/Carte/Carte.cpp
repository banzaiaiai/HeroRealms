#include "backEnd/Carte/Carte.hpp"

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

Carte::Carte(const std::string& name, int coupOr, Faction faction)
    : _id(_nextId++),
      _name(name),
      _coupOr(coupOr),
      _faction(faction)
{
    std::cout << "Creation carte avec paramètres" << std::endl;
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