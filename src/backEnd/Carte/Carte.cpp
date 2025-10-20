#include "backEnd/Carte/Carte.hpp"

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

void Carte::addTrigger(EventType eventType,
                       std::vector<std::shared_ptr<IEffect>> effects)
{
    _trigger[eventType] = std::move(effects);
}

