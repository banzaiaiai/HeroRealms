#ifndef IEFFECT_H
#define IEFFECT_H

class IEffect {
public:
    virtual ~IEffect() = default;
    virtual void applyEffect() = 0;  // Méthode virtuelle pure
};

#endif // IEFFECT_H
