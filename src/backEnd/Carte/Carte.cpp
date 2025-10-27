#include "backEnd/Carte/Carte.hpp"
#include "backEnd/Partie.hpp"

Carte::Carte() 
{
    //_carteGraphique = CarteGraphique();
}
Carte::Carte(CarteGraphique* carteGraphique):_carteGraphique(carteGraphique)
{
    
}
Carte::~Carte() {}

bool Carte::operator==(const Carte &other) const{
    if( other.getFaction() == _faction && 
        other.getCoupOr() == _coupOr &&
        other.getName() == _name)
    {
        return true;
    }
    return false;
}
bool Carte::operator==(const Carte *other) const{
    if( other->getFaction() == _faction && 
        other->getCoupOr() == _coupOr &&
        other->getName() == _name)
    {
        return true;
    }
    return false;
}

void Carte::addTrigger(EventType eventType,
                       std::vector<std::shared_ptr<IEffect>> effects)
{
    _trigger[eventType] = std::move(effects);
}

void Carte::jouer(Partie* partie)
{
    auto it = _trigger.find(EventType::OnPlay);
    if (it != _trigger.end()) {
        for (const auto& effect : it->second) {
            effect->applyEffect(partie);
        }
    }
}