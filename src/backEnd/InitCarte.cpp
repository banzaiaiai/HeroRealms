#include "backEnd/InitCarte.hpp"

// Fonction utilitaire privée
void InitCarte::addCarte(std::vector<std::unique_ptr<Carte>>& res,
                         const std::string& name,
                         int cout,
                         Faction faction,
                         const std::string& path,
                         std::shared_ptr<IEffect> effet)
{
    auto c = std::make_unique<Carte>(name, cout, faction, path);
    c->addTrigger(EventType::OnPlay, std::vector<std::shared_ptr<IEffect>>{ effet });
    res.push_back(std::move(c));
}

// Deck de base
std::vector<std::unique_ptr<Carte>> InitCarte::deckDeBase() {
    std::vector<std::unique_ptr<Carte>> res;

    // 7 gold
    for (int i = 0; i < 7; ++i)
        addCarte(res, "gold", 0, Faction::Neutre,
                 "assets/carte/BAS-EN-097-gold.jpg",
                 std::make_shared<GainGold>(1));

    // 1 ruby
    addCarte(res, "ruby", 0, Faction::Neutre,
             "assets/carte/BAS-EN-133-ruby.jpg",
             std::make_shared<GainGold>(2));

    // 1 dagger
    addCarte(res, "dagger", 0, Faction::Neutre,
             "assets/carte/BAS-EN-129-dagger.jpg",
             std::make_shared<DamageEffect>(1));

    // 1 shortsword
    addCarte(res, "shortsword", 0, Faction::Neutre,
             "assets/carte/BAS-EN-125-shortsword.jpg",
             std::make_shared<DamageEffect>(2));

    return res;
}

// Fire Gems
std::vector<std::unique_ptr<Carte>> InitCarte::fireGems() {
    return {};
}

// Marche
std::vector<std::unique_ptr<Carte>> InitCarte::marche() {
    return {};
}
