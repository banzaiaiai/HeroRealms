#ifndef SFMLGAME_HPP
#define SFMLGAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <memory>
#include <map>
#include "frontEnd/GestionnaireZones.hpp"
#include "frontEnd/CarteGraphique.hpp"
#include "frontEnd/Overlay.hpp"
#include "frontEnd/Button.hpp"

class Partie;
class Carte;
class ZoneCarte;

/**
 * SFMLGame - Interface graphique du jeu
 * Observe l'état de la partie et affiche les cartes par ID
 * NE POSSÈDE PAS les cartes logiques, seulement leur représentation graphique
 */
class SFMLGame {
private:
    Partie* _partie;  // Pointeur non-owning vers la partie
    GestionnaireZones _zones;
    
    // Carte graphiques indexées par l'ID de la carte logique
    std::map<int, std::unique_ptr<CarteGraphique>> _cartesGraphiques;
    
    // Gestion de la sélection (par ID)
    CarteGraphique* _carteSelectionnee;
    int _carteSelectionneeId;
    sf::Vector2f _positionOriginale;
    ZoneCarte* _zoneSource;
    
    // UI
    Overlay _overlay;
    Button _buttonAtacker;
    Button _buttonFinTour;

    Button _buttonDefausse1;
    Button _buttonDefausse2;

    Button _buttonpioche1;
    Button _buttonpioche2;

    Button _buttondeffausse;

    sf::RenderWindow _window;
    sf::Font _font;
    sf::Text _textJoueur1;
    sf::Text _textJoueur2;

    sf::RectangleShape _rectangeHaut;
    sf::RectangleShape _rectangeBas;

    sf::RectangleShape _backCarteHaut;
    sf::RectangleShape _backCarteBas;
    // Textures must outlive the shapes that reference them
    sf::Texture _backCarteTexture;

public:
    /**
     * Constructeur
     * @param partie Pointeur non-owning vers la partie
     */
    SFMLGame(Partie* partie);
    
    /**
     * Destructeur
     */
    ~SFMLGame();
    
    /**
     * Change la partie observée
     */
    void setPartie(Partie* partie);
    
    /**
     * Boucle principale du jeu
     */
    void gameLoop();

private:
    /**
     * Synchronise l'affichage avec l'état logique de la partie
     * Crée/détruit les CarteGraphique selon les cartes existantes
     */
    void synchroniserAffichage();
    
    /**
     * Crée une carte graphique pour une carte logique
     */
    void creerCarteGraphique( const Carte* carte);
    
    /**
     * Traite les événements SFML
     */
    void processEvents();
    
    /**
    *Fin de Tour
    */
    void finDeTour();
    /**
     * Gère le clic de souris
     */
    void handleMouseClick(int mouseX, int mouseY);
    
    /**
     * Gère le relâchement de la souris (fin du drag & drop)
     */
    void handleMouseRelease(int mouseX, int mouseY);
    
    /**
     * Met à jour l'état du jeu
     */
    void update();
    
    /**
     * Affiche le jeu
     */
    void render();
    
    /**
     * Initialise les textes
     */
    void rendertext();
    
    /**
     * Vérifie si un déplacement est valide selon les règles
     * @param carteId ID de la carte à déplacer
     */
    bool deplacementValide(ZoneCarte* source, ZoneCarte* cible, int carteId);
    
    /**
     * Applique le déplacement dans la logique métier
     * @param carteId ID de la carte à déplacer
     */
    void appliquerDeplacementLogique(int carteId, ZoneCarte* source, ZoneCarte* cible);
};

#endif // SFMLGAME_HPP
