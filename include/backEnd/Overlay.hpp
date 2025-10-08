#ifndef OVERLAY_H
#define OVERLAY_H

#include "backEnd/Carte/Carte.hpp"
#include <vector>
#include <functional>

class Overlay {
public:
    Overlay();
    ~Overlay();
    void afficher(std::vector<Carte> listCarte, std::function<bool(Carte carte)> fn);
};

#endif // OVERLAY_H
