#ifndef PREPARECHAMPION_H
#define PREPARECHAMPION_H

#include "backEnd/Effect/IEffect.hpp"
#include "backEnd/Joueur.hpp"

// Forward declaration pour éviter les dépendances circulaires
class Champion;

class PrepareChampion : public IEffect {

public:
    PrepareChampion();
    ~PrepareChampion() override = default;
    
    void applyEffect(Joueur *joueur) override;

};

#endif // PREPARECHAMPION_H
