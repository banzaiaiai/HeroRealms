#include "backEnd/InitCarte.hpp"


// Fonction utilitaire privée
void InitCarte::addNonPermanent(
    std::vector<std::unique_ptr<Carte>>& res,
    int count,
    const std::string& name,
    int cout,
    Faction faction,
    const std::string& path,
    NonPermanent::Type type,
    const std::vector<std::pair<EventType, std::vector<std::shared_ptr<IEffect>>>>& triggers)
{
    for (int i = 0; i < count; ++i) {
        auto c = std::make_unique<NonPermanent>(name, cout, faction, path, type);

        for (const auto& [event, effets] : triggers) {
            c->addTrigger(event, effets);
        }

        res.push_back(std::move(c));
    }
}

void InitCarte::addChampion(
    std::vector<std::unique_ptr<Carte>>& res,
    int count,
    const std::string& name,
    int cout,
    Faction faction,
    const std::string& path,
    int pvTotal,
    bool gardien,
    const std::vector<std::pair<EventType, std::vector<std::shared_ptr<IEffect>>>>& triggers)
{
    for (int i = 0; i < count; ++i) {
        auto c = std::make_unique<Champion>(name, cout, faction, path, pvTotal, gardien);

        for (const auto& [event, effets] : triggers) {
            c->addTrigger(event, effets);
        }

        res.push_back(std::move(c));
    }
}



// Deck de base
std::vector<std::unique_ptr<Carte>> InitCarte::deckDeBase() {
    std::vector<std::unique_ptr<Carte>> res;

    // 7 gold
    addNonPermanent(res, 7, "gold", 0, Faction::Neutre,
                    "assets/carte/BAS-EN-097-gold.jpg",
                    NonPermanent::Type::Object,
                    {{ EventType::OnPlay, {std::make_shared<GainGold>(1)} }});

    // 1 ruby
    addNonPermanent(res, 1, "ruby", 0, Faction::Neutre,
                    "assets/carte/BAS-EN-133-ruby.jpg",
                    NonPermanent::Type::Object,
                    {{ EventType::OnPlay, {std::make_shared<GainGold>(2)} }});

    // 1 dagger
    addNonPermanent(res, 1, "dagger", 0, Faction::Neutre,
                    "assets/carte/BAS-EN-129-dagger.jpg",
                    NonPermanent::Type::Object,
                    {{ EventType::OnPlay, {std::make_shared<DamageEffect>(1)} }});

    // 1 shortsword
    addNonPermanent(res, 1, "shortsword", 0, Faction::Neutre,
                    "assets/carte/BAS-EN-125-shortsword.jpg",
                    NonPermanent::Type::Object,
                    {{ EventType::OnPlay, {std::make_shared<DamageEffect>(2)} }});

    return res;
}

// Fire Gems
std::vector<std::unique_ptr<Carte>> InitCarte::fireGems() {
    std::vector<std::unique_ptr<Carte>> res;

    // 16 fire gem
    addNonPermanent(res, 16, "fire-gem", 2, Faction::Neutre,
                    "assets/carte/BAS-EN-081-fire-gem.jpg",
                    NonPermanent::Type::Object,
                    {
                        {EventType::OnPlay,   {std::make_shared<GainGold>(2)} },
                        {EventType::OnDelete, {std::make_shared<DamageEffect>(3)} }
                    });

    return res;
}

// Marche
std::vector<std::unique_ptr<Carte>> InitCarte::marcher() {
    std::vector<std::unique_ptr<Carte>> res;

    
    addChampion(    res, 2, "Man at Arms", 3, Faction::Imperiale,
                    "assets/carte/HRBAS_Card_ManAtArms.jpg",
                    4, true,
                    {
                        {EventType::OnEngage, {std::make_shared<DamageEffect>(2, OccurenceType::Guard, 1)} }
                    });

    addNonPermanent(res, 1, "Close Rank", 3, Faction::Imperiale,
                    "assets/carte/BAS-EN-002-close-ranks.jpg",
                    NonPermanent::Type::Action,
                    {
                        {EventType::OnPlay,   {std::make_shared<DamageEffect>(5, OccurenceType::Champion, 2)} },
                        {EventType::OnAllyEnter, {std::make_shared<HealEffect>(6)} }
                    });
    
    addChampion(    res, 1, "Master Weyan", 4, Faction::Imperiale,
                    "assets/carte/BAS-EN-010-master-weyan.jpg",
                    4, true,
                    {
                        {EventType::OnEngage, {std::make_shared<DamageEffect>(3, OccurenceType::Champion, 1)} }
                    });

    addNonPermanent(res, 3, "Recruit", 2, Faction::Imperiale,
                    "assets/carte/BAS-EN-012-recruit.jpg",
                    NonPermanent::Type::Action,
                    {
                        {EventType::OnPlay, {
                            std::make_shared<GainGold>(2),
                            std::make_shared<HealEffect>(3, OccurenceType::Champion, 1),
                        } },
                        {EventType::OnAllyEnter, {std::make_shared<GainGold>(1)} }
                    });

    addNonPermanent(res, 3, "taxation", 1, Faction::Imperiale,
                    "assets/carte/BAS-EN-017-taxation.jpg",
                    NonPermanent::Type::Action,
                    {
                        {EventType::OnPlay, {std::make_shared<GainGold>(2)} },
                        {EventType::OnAllyEnter, {std::make_shared<HealEffect>(6)} }
                    });


    addChampion(    res, 1, "Borg, Ogre Mercenary", 6, Faction::Guilde,
                    "assets/carte/BAS-EN-021-borg-ogre-mercenary.jpg",
                    6, true,
                    {
                        {EventType::OnEngage, {std::make_shared<DamageEffect>(4)} }
                    });

    addNonPermanent(res, 2, "Intimidation", 2, Faction::Guilde,
                    "assets/carte/BAS-EN-029-intimidation.jpg",
                    NonPermanent::Type::Action,
                    {
                        {EventType::OnPlay, {std::make_shared<DamageEffect>(5)} },
                        {EventType::OnAllyEnter, {std::make_shared<GainGold>(2)} }
                    });

    addChampion(    res, 1, "Myros, Guild Mage", 5, Faction::Guilde,
                    "assets/carte/BAS-EN-031-myros-guild-mage.jpg",
                    3, true,
                    {
                        {EventType::OnEngage, {std::make_shared<GainGold>(3)} },
                        {EventType::OnAllyEnter, {std::make_shared<DamageEffect>(4)} }
                    });

    addNonPermanent(res, 3, "Profit", 1, Faction::Guilde,
                    "assets/carte/BAS-EN-033-profit.jpg",
                    NonPermanent::Type::Action,
                    {
                        {EventType::OnPlay, {std::make_shared<GainGold>(2)} },
                        {EventType::OnAllyEnter, {std::make_shared<DamageEffect>(4)} }
                    });

    addChampion(    res, 2, "Death Cultist", 2, Faction::Necros,
                    "assets/carte/BAS-EN-045-death-cultist.jpg",
                    3, true,
                    {
                        {EventType::OnEngage, {std::make_shared<DamageEffect>(2)} },
                    });
    
    addNonPermanent(res, 3, "Influence", 2, Faction::Necros,
                    "assets/carte/BAS-EN-051-influence.jpg",
                    NonPermanent::Type::Action,
                    {
                        {EventType::OnPlay, {std::make_shared<GainGold>(3)} },
                        {EventType::OnDelete, {std::make_shared<DamageEffect>(3)} }
                    });

    addChampion(    res, 1, "Dire Wolf", 5, Faction::Sauvage,
                    "assets/carte/BAS-EN-063-dire-wolf.jpg",
                    5, true,
                    {
                        {EventType::OnEngage, {std::make_shared<DamageEffect>(3)} },
                        {EventType::OnAllyEnter, {std::make_shared<DamageEffect>(4)} }
                    });

    addChampion(    res, 2, "Wolf Shaman", 2, Faction::Sauvage,
                    "assets/carte/BAS-EN-079-wolf-shaman.jpg",
                    4, false,
                    {
                        {EventType::OnEngage, {std::make_shared<DamageEffect>(2, OccurenceType::CarteSauvage, 1)} }
                    });





    auto rng = std::default_random_engine {};
    std::shuffle(std::begin(res), std::end(res), rng);

    return res;
}
