#ifndef PREPARECHAMPION_H
#define PREPARECHAMPION_H

#include "backEnd/Effect/IEffect.hpp"
#include "backEnd/Joueur.hpp"

// Forward declaration pour éviter les dépendances circulaires
class Champion;

class PrepareChampion : public IEffect {
private:
    Champion* _champion;

public:
    PrepareChampion(Champion* champion = nullptr);
    ~PrepareChampion() override = default;
    
    void applyEffect(Joueur *joueur) override;

    inline Champion* getChampion() const { return _champion; }
    inline void setChampion(Champion* champion) { _champion = champion; }
};

#endif // PREPARECHAMPION_H
