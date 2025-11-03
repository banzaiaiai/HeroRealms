#ifndef OREFFECT_H
#define OREFFECT_H

#include "backEnd/Effect/IEffect.hpp"
#include "backEnd/Joueur.hpp"
#include "backEnd/Carte/Carte.hpp"
#include "backEnd/Carte/Champion.hpp"
#include <string>
#include <vector>

class OrEffect : public IEffect {
private:
    std::string _name;
    std::vector<IEffect> _listeEffect;
    
public:
    OrEffect(std::string name, std::vector<IEffect> listeEffect);

    ~OrEffect() override = default;
    
    void applyEffect(Joueur *joueur) override;  // Implémentation

    // Getters et setters...
    inline std::string getName() const { return _name; }
    inline void setName(std::string name) { _name = name; }
};

#endif // DAMAGEEFFECT_H
