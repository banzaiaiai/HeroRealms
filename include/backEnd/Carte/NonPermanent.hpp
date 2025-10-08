#ifndef NONPERMANENT_H
#define NONPERMANENT_H

#include "backEnd/Carte/Carte.hpp"

class NonPermanent : public Carte {
private:
    enum Type { Object, Action } _type;

public:
    NonPermanent();
    ~NonPermanent();
    // Getters
    inline Type getType() const { return _type; }

    // Setters
    inline void setType(Type type) { _type = type; }
};

#endif // NONPERMANENT_H
