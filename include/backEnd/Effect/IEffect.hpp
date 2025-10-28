#ifndef IEFFECT_H
#define IEFFECT_H

class Joueur;
class Partie;

class IEffect {
public:
    virtual ~IEffect() = default;
    virtual void applyEffect(Joueur *joueur) = 0;  // Méthode virtuelle pure
};

#endif // IEFFECT_H
