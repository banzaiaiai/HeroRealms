
#ifndef OVERLAY_H
#define OVERLAY_H

#include <SFML/Graphics.hpp>
#include "backEnd/Carte/Carte.hpp"
#include "frontEnd/ZoneCarte.hpp"
#include "frontEnd/GestionnaireZones.hpp"
#include "frontEnd/CarteGraphique.hpp"
#include <vector>

class Overlay {
private:
    sf::RenderWindow _window;
    ZoneCarte _zoneCarte;
    std::vector<const Carte*> _listCarte;
    std::vector<CarteGraphique> _listCarteGraphique;

    void render();

public:
    Overlay();
    ~Overlay() {};

    int openOverlay(std::vector<const Carte*> listCarte,
                             std::string titre);
    

    template<typename... Vecs>
    int openOverlay(std::string titre, const Vecs&... vecs) {
        std::vector<const Carte*> toutesCartes;
        toutesCartes.reserve((vecs.size() + ...)); // C++17 fold expression
        (appendRawPtrs(toutesCartes, vecs), ...);  // append chaque vecteur
        return openOverlay(toutesCartes, titre);   // version existante
    }

private:
    template<typename T>
    void appendRawPtrs(std::vector<const T*>& dest, const std::vector<std::unique_ptr<T>>& src) {
        for (auto& c : src) dest.push_back(c.get());
    }
    template<typename T>
    void appendRawPtrs(std::vector<const T*>& dest, const std::vector<const T*>& src) {
    dest.insert(dest.end(), src.begin(), src.end());
}

};

#endif

