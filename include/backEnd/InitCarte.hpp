#ifndef INITCARTE_H
#define INITCARTE_H

#include <vector>
#include <memory>
#include "backEnd/Carte/Carte.hpp"
#include "backEnd/Effect/IEffect.hpp"
#include "backEnd/Effect/DamageEffect.hpp"
#include "backEnd/Effect/GainGold.hpp"

class InitCarte {
public:
    static std::vector<std::unique_ptr<Carte>> deckDeBase();
    static std::vector<std::unique_ptr<Carte>> fireGems();
    static std::vector<std::unique_ptr<Carte>> marche();

private:
    static void addCarte(std::vector<std::unique_ptr<Carte>>& res,
                         const std::string& name,
                         int cout,
                         Faction faction,
                         const std::string& path,
                         std::shared_ptr<IEffect> effet);
};

#endif
