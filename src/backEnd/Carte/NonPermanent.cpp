#include "backEnd/Carte/NonPermanent.hpp"


NonPermanent::NonPermanent(const std::string& name, int coupOr, Faction faction,
             std::string imagePath, Type type)
    : Carte(name, coupOr, faction, imagePath), _type(type) {};

NonPermanent::~NonPermanent() {}
