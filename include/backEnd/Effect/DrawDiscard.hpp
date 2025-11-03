#ifndef DRAWDISCARD_H
#define DRAWDISCARD_H

#include "backEnd/Effect/IEffect.hpp"
#include "backEnd/Joueur.hpp"
#include "backEnd/Carte/Carte.hpp"
#include <string>
#include <vector>

class DrawDiscard : public IEffect {
private:
    std::string _name;
    std::vector<std::shared_ptr<IEffect>> _listeEffect;
    
public:
    DrawDiscard();

    ~DrawDiscard() override = default;
    
    void applyEffect(Joueur *joueur) override;  // Implémentation

    // Getters et setters...
    inline std::string getName() const { return _name; }
    inline void setName(std::string name) { _name = name; }
};

#endif // DAMAGEEFFECT_H
