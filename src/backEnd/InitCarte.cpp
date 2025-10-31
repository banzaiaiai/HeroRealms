#include "backEnd/InitCarte.hpp"

// Fonction utilitaire privée
void InitCarte::addNonPermanent(
    std::vector<std::unique_ptr<Carte>>& res,
    const std::string& name,
    int cout,
    Faction faction,
    const std::string& path,
    NonPermanent::Type type,
    const std::vector<std::pair<EventType, std::vector<std::shared_ptr<IEffect>>>>& triggers)
{
    auto c = std::make_unique<NonPermanent>(name, cout, faction, path, type);

    // On ajoute chaque trigger à la carte
    for (const auto& [event, effets] : triggers) {
        c->addTrigger(event, effets);
    }

    res.push_back(std::move(c));
}

void InitCarte::addChampion(
    std::vector<std::unique_ptr<Carte>>& res,
    const std::string& name,
    int cout,
    Faction faction,
    const std::string& path,
    int pvTotal,
    bool gardien,
    const std::vector<std::pair<EventType, std::vector<std::shared_ptr<IEffect>>>>& triggers)
{
    auto c = std::make_unique<Champion>(name, cout, faction, path, pvTotal, gardien);

    // On ajoute chaque trigger à la carte
    for (const auto& [event, effets] : triggers) {
        c->addTrigger(event, effets);
    }

    res.push_back(std::move(c));
}



// Deck de base
std::vector<std::unique_ptr<Carte>> InitCarte::deckDeBase() {
    std::vector<std::unique_ptr<Carte>> res;

    // 7 gold
    for (int i = 0; i < 7; ++i)
        addNonPermanent(res, "gold", 0, Faction::Neutre,
                        "assets/carte/BAS-EN-097-gold.jpg",
                        NonPermanent::Type::Object,
                        {{ EventType::OnPlay, {std::make_shared<GainGold>(1)} }});

    // 1 ruby
    addNonPermanent(res, "ruby", 0, Faction::Neutre,
                    "assets/carte/BAS-EN-133-ruby.jpg",
                    NonPermanent::Type::Object,
                    {{ EventType::OnPlay, {std::make_shared<GainGold>(2)} }});

    // 1 dagger
    addNonPermanent(res, "dagger", 0, Faction::Neutre,
                    "assets/carte/BAS-EN-129-dagger.jpg",
                    NonPermanent::Type::Object,
                    {{ EventType::OnPlay, {std::make_shared<DamageEffect>(1)} }});

    // 1 shortsword
    addNonPermanent(res, "shortsword", 0, Faction::Neutre,
                    "assets/carte/BAS-EN-125-shortsword.jpg",
                    NonPermanent::Type::Object,
                    {{ EventType::OnPlay, {std::make_shared<DamageEffect>(2)} }});

    return res;
}

// Fire Gems
std::vector<std::unique_ptr<Carte>> InitCarte::fireGems() {
    std::vector<std::unique_ptr<Carte>> res;

    // 16 gold
    for (int i = 0; i < 16; ++i)
        addNonPermanent(res, "fire-gem", 2, Faction::Neutre,
                        "assets/carte/BAS-EN-081-fire-gem.jpg",
                        NonPermanent::Type::Object,
                        {
                            {EventType::OnPlay,   {std::make_shared<GainGold>(2)} },
                            {EventType::OnDelete, {std::make_shared<DamageEffect>(3)} }
                        });

    return res;
}

// Marche
std::vector<std::unique_ptr<Carte>> InitCarte::marche() {
    std::vector<std::unique_ptr<Carte>> res;

    // 7 gold
    for (int i = 0; i < 7; ++i)
        addNonPermanent(res, "gold", 0, Faction::Neutre,
                        "assets/carte/BAS-EN-097-gold.jpg",
                        NonPermanent::Type::Object,
                        {{ EventType::OnPlay, {std::make_shared<GainGold>(1)} }});

    // 1 ruby
    addNonPermanent(res, "ruby", 0, Faction::Neutre,
                    "assets/carte/BAS-EN-133-ruby.jpg",
                    NonPermanent::Type::Object,
                    {{ EventType::OnPlay, {std::make_shared<GainGold>(2)} }});

    // 1 dagger
    addNonPermanent(res, "dagger", 0, Faction::Neutre,
                    "assets/carte/BAS-EN-129-dagger.jpg",
                    NonPermanent::Type::Object,
                    {{ EventType::OnPlay, {std::make_shared<DamageEffect>(1)} }});

    // 1 shortsword
    addNonPermanent(res, "shortsword", 0, Faction::Neutre,
                    "assets/carte/BAS-EN-125-shortsword.jpg",
                    NonPermanent::Type::Object,
                    {{ EventType::OnPlay, {std::make_shared<DamageEffect>(2)} }});

    return res;
}
