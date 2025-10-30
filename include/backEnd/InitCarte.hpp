#ifndef INITCARTE_H
#define INITCARTE_H

#include <vector>
#include <memory>
#include "backEnd/Carte/Carte.hpp"

class InitCarte {
public:
    static std::vector<std::unique_ptr<Carte>> deckDeBase();
    static std::vector<std::unique_ptr<Carte>> fireGems();
    static std::vector<std::unique_ptr<Carte>> marche();
};

#endif
