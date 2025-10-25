#ifndef ZONECARTE_HPP
#define ZONECARTE_HPP

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>
#include <vector>
#include <memory>

// Forward declaration
class Carte;

class ZoneCarte {
    friend class Overlay;
    friend class SFMLGame;
private:
    sf::FloatRect _zone;
    std::string _nom;
    sf::Color _couleurFond;
    std::vector<Carte*> _cartesLogiques;  // Références vers les cartes logiques
    
public:
    ZoneCarte(float x, float y, float width, float height, 
              const std::string& nom, 
              const sf::Color& couleur = sf::Color(100, 100, 100, 100));
    
    // Gestion des cartes logiques
    void ajouterCarteLogique(Carte* carte);
    void retirerCarteLogique(Carte* carte);
    void viderCartes();
    
    // Accès
    bool contient(const sf::Vector2f& point) const;
    void dessiner(sf::RenderWindow& window) const;
    
    // Calcul des positions pour l'affichage
    std::vector<sf::Vector2f> calculerPositionsCartes() const;
    
    // Getters
    inline const std::string& getNom() const { return _nom; }
    inline const sf::FloatRect& getBounds() const { return _zone; }
    inline const std::vector<Carte*>& getCartesLogiques() const { return _cartesLogiques; }
    inline bool estVide() const { return _cartesLogiques.empty(); }
    inline size_t getNbCartes() const { return _cartesLogiques.size(); }
    
    // Recherche
    bool contientCarte(const Carte* carte) const;
};

#endif
