#ifndef SACRIFICECARD_H
#define SACRIFICECARD_H

#include "backEnd/Effect/IEffect.hpp"
#include "backEnd/Joueur.hpp"

// Forward declaration pour éviter les dépendances circulaires
class Champion;

class SacrificeCard : public IEffect {
private:
    int _damageForSacrifice;
public:
    SacrificeCard(int damageForSacrifice = 0);
    ~SacrificeCard() override = default;
    
    void applyEffect(Joueur *joueur) override;

};

#endif // PREPARECHAMPION_H
