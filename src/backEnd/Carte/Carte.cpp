#include "backEnd/Carte/Carte.hpp"

Carte::Carte() {}
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

void Carte::addTrigger(EventType eventType,
                       std::vector<std::unique_ptr<IEffect>> effects)
{
    _trigger[eventType] = std::move(effects);
}

