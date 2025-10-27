#ifndef IEFFECT_H
#define IEFFECT_H

class Partie;

class IEffect {
public:
    virtual ~IEffect() = default;
    virtual void applyEffect(Partie *partie) = 0;  // Méthode virtuelle pure
};

#endif // IEFFECT_H
