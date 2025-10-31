#include "backEnd/Carte/Carte.hpp"
#include "backEnd/Effect/DamageEffect.hpp"
#include "backEnd/Effect/IEffect.hpp"
#include "backEnd/Joueur.hpp"
#include "backEnd/Partie.hpp"
#include "frontEnd/SFMLGame.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <vector>

/**
 * Fonction utilitaire pour créer une carte avec des effets
 */
std::unique_ptr<Carte> creerCarteDegat(const std::string& nom, int degats, int cout) {
    auto carte = std::make_unique<Carte>(nom, cout, Faction::Neutre, "assets/carte/hero_realms_back.jpg");
    
    // Créer l'effet de dégâts
    std::vector<std::shared_ptr<IEffect>> effets;
    effets.push_back(std::make_shared<DamageEffect>(degats));
    
    carte->addTrigger(EventType::OnPlay, effets);
    
    return carte;
}

/**
 * Crée un deck de cartes pour un joueur
 */
std::vector<std::unique_ptr<Carte>> creerDeck(int tailleDeck) {
    std::vector<std::unique_ptr<Carte>> deck;
    deck.reserve(tailleDeck);
    
    for (int i = 0; i < tailleDeck; i++) {
        // Créer des cartes variées
        if (i % 3 == 0) {
            deck.push_back(creerCarteDegat("Épée", 5, 2));
        } else if (i % 3 == 1) {
            deck.push_back(creerCarteDegat("Lance", 3, 1));
        } else {
            deck.push_back(creerCarteDegat("Arc", 7, 3));
        }
    }
    
    return deck;
}

int main() {
    std::cout << "=== Initialisation du jeu ===" << std::endl;
    
    // Créer une partie
    Partie partie = Partie();
    
    // Initialiser le marché
    std::cout << "Initialisation du marché..." << std::endl;
    for (int i = 0; i < 5; i++) {
        partie.ajouterCarteRiviere(creerCarteDegat("Marché Carte " + std::to_string(i), 4, 2));
    }
    
    // Lancer l'interface SFML
    std::cout << "\n=== Lancement de l'interface graphique ===" << std::endl;
    SFMLGame jeu(&partie);

    //partie.overlay->openOverlay("test", creerDeck(40)); // test de l'overlay
    
    jeu.gameLoop();
    
    return 0;
}
