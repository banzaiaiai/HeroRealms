#ifndef ZONECARTE_HPP
#define ZONECARTE_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Carte;

/**
 * ZoneCarte - Zone graphique qui OBSERVE des cartes
 * N'a AUCUNE propriété sur les cartes
 * Utilise des pointeurs const pour lecture seule
 */
class ZoneCarte {
    friend class Overlay;
    friend class SFMLGame;
private:
    float _x, _y, _width, _height;
    std::string _nom;
    sf::Color _couleur;
    sf::RectangleShape _shape;
    
    // POINTEURS NON-OWNING vers les cartes observées
    std::vector<const Carte*> _cartesObservees;

public:
    ZoneCarte(float x, float y, float width, float height, 
              const std::string& nom, sf::Color couleur);
    
    ~ZoneCarte();
    
    // === GETTERS ===
    std::string getNom() const { return _nom; }
    sf::Vector2f getPosition() const { return sf::Vector2f(_x, _y); }
    sf::Vector2f getSize() const { return sf::Vector2f(_width, _height); }
    
    /**
     * Retourne les cartes observées (pointeurs non-owning)
     */
    const std::vector<const Carte*>& getCartesObservees() const { 
        return _cartesObservees; 
    }
    
    // === OBSERVATION DES CARTES ===
    
    /**
     * Vide la liste des cartes observées
     */
    void viderCartes();
    
    /**
     * Ajoute une carte à observer (pointeur non-owning)
     */
    void observerCarte(const Carte* carte);
    
    /**
     * Retire une carte de l'observation
     */
    void arreterObserver(const Carte* carte);
    
    // === UTILITAIRES ===
    
    /**
     * Vérifie si un point est dans la zone
     */
    bool contient(const sf::Vector2f& point) const;
    
    /**
     * Calcule les positions pour afficher les cartes
     * @return Vecteur de positions pour chaque carte
     */
    std::vector<sf::Vector2f> calculerPositionsCartes() const;
    
    /**
     * Dessine la zone (bordure, fond)
     */
    void dessiner(sf::RenderWindow& window) const;
};

#endif // ZONECARTE_HPP
