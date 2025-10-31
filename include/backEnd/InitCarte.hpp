#ifndef INITCARTE_H
#define INITCARTE_H

#include <vector>
#include <memory>
#include "backEnd/Carte/Carte.hpp"
#include "backEnd/Carte/Champion.hpp"
#include "backEnd/Carte/NonPermanent.hpp"
#include "backEnd/Effect/IEffect.hpp"
#include "backEnd/Effect/DamageEffect.hpp"
#include "backEnd/Effect/HealEffect.hpp"
#include "backEnd/Effect/GainGold.hpp"

class InitCarte {
public:
    static std::vector<std::unique_ptr<Carte>> deckDeBase();
    static std::vector<std::unique_ptr<Carte>> fireGems();
    static std::vector<std::unique_ptr<Carte>> marcher();

private:
    static void addNonPermanent(std::vector<std::unique_ptr<Carte>>& res,
                                int count,
                                const std::string& name,
                                int cout,
                                Faction faction,
                                const std::string& path,
                                NonPermanent::Type type,
                                const std::vector<std::pair<EventType, std::vector<std::shared_ptr<IEffect>>>>& triggers);

    static void addChampion(std::vector<std::unique_ptr<Carte>>& res,
                            int count,
                            const std::string& name,
                            int cout,
                            Faction faction,
                            const std::string& path,
                            int pvTotal,
                            bool gardien,
                            const std::vector<std::pair<EventType, std::vector<std::shared_ptr<IEffect>>>>& triggers);
};

#endif
