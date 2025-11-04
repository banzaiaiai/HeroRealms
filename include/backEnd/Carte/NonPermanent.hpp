#ifndef NONPERMANENT_H
#define NONPERMANENT_H

#include "backEnd/Carte/Carte.hpp"

class NonPermanent : public Carte {
public:
    enum class Type { Object, Action };

private:
    Type _type;

public:
    NonPermanent(const std::string& name, int coupOr, Faction faction,
                 std::string imagePath, Type type); 
    ~NonPermanent();

    Type getType() const { return _type; };

    bool estChampion() const override { return false; }
};

#endif // NONPERMANENT_H
