#include "frontEnd/ZoneCarte.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include "backEnd/Carte/Carte.hpp"
#include <algorithm>
#include <iostream>

ZoneCarte::ZoneCarte(float x, float y, float width, float height, 
                     const std::string& nom, const sf::Color& couleur) 
    : _zone(x, y, width, height), 
      _nom(nom), 
      _couleurFond(couleur)
{
}

// Gestion des cartes logiques
void ZoneCarte::ajouterCarteLogique(Carte* carte) {
    //if (carte && !contientCarte(carte)) {
        _cartesLogiques.push_back(carte);
        //std::cout << "Carte '" << carte->getName() << "' ajoutée à la zone '" << _nom << "'" << std::endl;
    //}
}

void ZoneCarte::retirerCarteLogique(Carte* carte) {
    auto it = std::find(_cartesLogiques.begin(), _cartesLogiques.end(), carte);
    if (it != _cartesLogiques.end()) {
        _cartesLogiques.erase(it);
        std::cout << "Carte '" << carte->getName() << "' retirée de la zone '" << _nom << "'" << std::endl;
    }
}

void ZoneCarte::viderCartes() {
    _cartesLogiques.clear();
}

bool ZoneCarte::contientCarte(const Carte* carte) const {
    return std::find(_cartesLogiques.begin(), _cartesLogiques.end(), carte) != _cartesLogiques.end();
}

bool ZoneCarte::contient(const sf::Vector2f& point) const {
    return _zone.contains(point);
}

void ZoneCarte::dessiner(sf::RenderWindow& window) const {
    sf::RectangleShape fond(sf::Vector2f(_zone.width, _zone.height));
    fond.setPosition(_zone.left, _zone.top);
    fond.setFillColor(_couleurFond);
    fond.setOutlineColor(sf::Color::White);
    fond.setOutlineThickness(2.f);
    window.draw(fond);
    
    // Optionnel: Afficher le nombre de cartes dans la zone
    // (Tu pourrais ajouter du texte SFML ici)
}

std::vector<sf::Vector2f> ZoneCarte::calculerPositionsCartes() const {
    std::vector<sf::Vector2f> positions;
    
    if (_cartesLogiques.empty()) {
        return positions;
    }
    
    float largeurCarte = 80.f;
    float hauteurCarte = 120.f;
    float espacement = 10.f;
    
    // Calculer le nombre maximum de cartes par ligne
    int maxCartesParLigne = static_cast<int>((_zone.width - espacement) / (largeurCarte + espacement));
    if (maxCartesParLigne <= 0) maxCartesParLigne = 1;
    
    // Calculer le nombre de lignes nécessaires
    int nbLignes = (_cartesLogiques.size() + maxCartesParLigne - 1) / maxCartesParLigne;
    
    // Centrer les cartes dans la zone
    float largeurTotale = std::min(static_cast<int>(_cartesLogiques.size()), maxCartesParLigne) * (largeurCarte + espacement) - espacement;
    float offsetX = _zone.left + (_zone.width - largeurTotale) / 2;
    float offsetY = _zone.top + (_zone.height - (nbLignes * (hauteurCarte + espacement))) / 2;
    
    // Calculer les positions
    for (size_t i = 0; i < _cartesLogiques.size(); i++) {
        int ligne = i / maxCartesParLigne;
        int colonne = i % maxCartesParLigne;
        
        float x = offsetX + colonne * (largeurCarte + espacement);
        float y = offsetY + ligne * (hauteurCarte + espacement);
        
        positions.emplace_back(x, y);
    }
    
    return positions;
}
