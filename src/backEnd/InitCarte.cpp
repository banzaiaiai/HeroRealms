#include "backEnd/InitCarte.hpp"
#include "backEnd/Carte/Carte.hpp"
#include "backEnd/Effect/DrawCard.hpp"
#include "backEnd/Effect/GainGold.hpp"
#include "backEnd/Effect/NextCardRecup.hpp"
#include "backEnd/Effect/RecupCard.hpp"
#include "backEnd/Joueur.hpp"
#include "frontEnd/ZoneCarte.hpp"
#include <memory>


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

    
    addChampion(    res, 1, "Arkus, Imperial Dragon", 8, Faction::Imperiale,
                    "assets/carte/BAS-EN-001-arkus-imperial-dragon.jpg",
                    6, true,
                    {
                        {EventType::OnEngage, {
                                std::make_shared<DamageEffect>(5),
                                std::make_shared<DrawCard>(1)
                        }},
                        {EventType::OnAllyEnter, {std::make_shared<HealEffect>(6)} }
                    });

    addNonPermanent(res, 1, "Close Rank", 3, Faction::Imperiale,
                    "assets/carte/BAS-EN-002-close-ranks.jpg",
                    NonPermanent::Type::Action,
                    {
                        {EventType::OnPlay,   {std::make_shared<DamageEffect>(5, OccurenceType::Champion, 2)} },
                        {EventType::OnAllyEnter, {std::make_shared<HealEffect>(6)} }
                    });

    addNonPermanent(res, 1, "Command", 5, Faction::Imperiale,
                    "assets/carte/BAS-EN-003-command.jpg",
                    NonPermanent::Type::Action,
                    {
                        {EventType::OnPlay, {
                            std::make_shared<GainGold>(2),
                            std::make_shared<DamageEffect>(3),
                            std::make_shared<HealEffect>(4),
                            std::make_shared<DrawCard>(1)
                        } },
                    });

    addChampion(    res, 1, "Cristov, the Just", 5, Faction::Imperiale,
                    "assets/carte/BAS-EN-006-cristov-the-just.jpg",
                    5, true,
                    {
                        {EventType::OnEngage, {
                                std::make_shared<DamageEffect>(2),
                                std::make_shared<HealEffect>(3)
                        }},
                        {EventType::OnAllyEnter, {std::make_shared<DrawCard>(1)} }
                    });
    
    addChampion(    res, 1, "Kraka, High Priest", 6, Faction::Imperiale,
                    "assets/carte/BAS-EN-007-kraka-high-priest.jpg",
                    6, false,
                    {
                        {EventType::OnEngage, {
                                std::make_shared<HealEffect>(2),
                                std::make_shared<DrawCard>(1)
                        }},
                        {EventType::OnAllyEnter, {std::make_shared<HealEffect>(0, OccurenceType::Champion, 2)} }
                    });
    
    addChampion(    res, 2, "Man at Arms", 3, Faction::Imperiale,
                    "assets/carte/HRBAS_Card_ManAtArms.jpg",
                    4, true,
                    {
                        {EventType::OnEngage, {std::make_shared<DamageEffect>(2, OccurenceType::Guard, 1)} }
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

    

    addNonPermanent(res, 1, "Word of Power", 6, Faction::Imperiale,
                    "assets/carte/BAS-EN-020-word-of-power.jpg",
                    NonPermanent::Type::Action,
                    {
                        {EventType::OnPlay, {std::make_shared<DrawCard>(2)} },
                        {EventType::OnAllyEnter, {std::make_shared<HealEffect>(5)} },
                        {EventType::OnDelete, {std::make_shared<DamageEffect>(5)} }
                    });

    addNonPermanent(res, 3, "Taxation", 1, Faction::Imperiale,
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

    addNonPermanent(res, 3, "Bribe", 3, Faction::Guilde, 
                    "assets/carte/BAS-EN-22-bribe.jpg",
                     NonPermanent::Type::Action,
                     {
                        {EventType::OnPlay,{std::make_shared<GainGold>(3)}},
                        {EventType::OnAllyEnter,{std::make_shared<NextCardRecup>(1,TypeCarte::Action,ZoneType::Pioche)}},
                     });
    
    addNonPermanent(res, 1, "Deception", 5, Faction::Guilde, 
                    "assets/carte/BAS-EN-26-deception.jpg",
                     NonPermanent::Type::Action,
                     {
                        {EventType::OnPlay,{std::make_shared<GainGold>(2),
                                                std::make_shared<DrawCard>(1)}},
                        {EventType::OnAllyEnter,{std::make_shared<NextCardRecup>(1,TypeCarte::Tous,ZoneType::Main)}},
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

    addChampion(    res, 1, "Parov, the Enforcer", 5, Faction::Guilde,
                    "assets/carte/BAS-EN-032-parov-the-enforcer.jpg",
                    5, true,
                    {
                        {EventType::OnEngage, {std::make_shared<DamageEffect>(3)} },
                        {EventType::OnAllyEnter, {std::make_shared<DrawCard>(4)} }
                    });

    addNonPermanent(res, 3, "Profit", 1, Faction::Guilde,
                    "assets/carte/BAS-EN-033-profit.jpg",
                    NonPermanent::Type::Action,
                    {
                        {EventType::OnPlay, {std::make_shared<GainGold>(2)} },
                        {EventType::OnAllyEnter, {std::make_shared<DamageEffect>(4)} }
                    });

    addChampion(    res, 1, "Rasmus, the Smuggler", 4, Faction::Guilde,
                    "assets/carte/BAS-EN-037-rasmus-the-smuggler.jpg",
                    5, false,
                    {
                        {EventType::OnEngage, {std::make_shared<GainGold>(2)} },
                        {EventType::OnAllyEnter, {std::make_shared<NextCardRecup>(1,TypeCarte::Tous,ZoneType::Pioche)}},
                    });
    addNonPermanent(res, 1, "Smash and Grab", 6, Faction::Guilde,
                    "assets/carte/BAS-EN-038-smash-and-grab.jpg",
                    NonPermanent::Type::Action,
                    {
                        {EventType::OnPlay,{std::make_shared<DamageEffect>(6),
                        std::make_shared<RecupCard>(1,TypeCarte::Tous,ZoneType::Defausse,ZoneType::Pioche)} }
                    });
    
    addNonPermanent(res, 1, "Dark Energy", 4, Faction::Necros,
                    "assets/carte/BAS-EN-043-dark-energy.jpg",
                    NonPermanent::Type::Action,
                    {
                        {EventType::OnPlay, {std::make_shared<DamageEffect>(7)} },
                        {EventType::OnAllyEnter, {std::make_shared<DrawCard>(1)} }
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
    addChampion(    res, 1, "Varrick, the Necromancer", 5, Faction::Necros,
                    "assets/carte/BAS-EN-060-varrick-the-necromancer.jpg",
                    3, false,
                    {
                        {EventType::OnEngage, {std::make_shared<RecupCard>(1,TypeCarte::Champion,ZoneType::Defausse,ZoneType::Pioche)} },
                        {EventType::OnAllyEnter, {std::make_shared<DrawCard>(1)} }
                    });
    addChampion(    res, 1, "Cron, the Berserker", 6, Faction::Sauvage,
                    "assets/carte/BAS-EN-062-cron-the-berserker.jpg",
                    6, false,
                    {
                        {EventType::OnEngage, {std::make_shared<DamageEffect>(5)} },
                        {EventType::OnAllyEnter, {std::make_shared<DrawCard>(1)} }
                    });

    addChampion(    res, 1, "Dire Wolf", 5, Faction::Sauvage,
                    "assets/carte/BAS-EN-063-dire-wolf.jpg",
                    5, true,
                    {
                        {EventType::OnEngage, {std::make_shared<DamageEffect>(3)} },
                        {EventType::OnAllyEnter, {std::make_shared<DamageEffect>(4)} }
                    });

    addChampion(    res, 2, "Orc Grunt", 3, Faction::Sauvage,
                    "assets/carte/BAS-EN-071-orc-grunt.jpg",
                    3, true,
                    {
                        {EventType::OnEngage, {std::make_shared<DamageEffect>(2)} },
                        {EventType::OnAllyEnter, {std::make_shared<DrawCard>(1)} }
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
