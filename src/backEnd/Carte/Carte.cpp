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

void Carte::addTrigger(EventType eventType, std::vector<IEffect> effects){
    _trigger.add(eventType, effects);
}
