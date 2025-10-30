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
    auto carte = std::make_unique<Carte>(nom, cout, Faction::Neutre, "assets/carte/hero_realms_back.png");
    
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
    
    // Créer les decks des joueurs
    auto deck1 = creerDeck(20);
    auto deck2 = creerDeck(20);
    
    std::cout << "Decks créés: " << deck1.size() << " et " << deck2.size() << " cartes" << std::endl;
    
    // Créer les joueurs
    Joueur joueur1(0, partie, "Alice");
    Joueur joueur2(1, partie, "Bob");
    
    // Initialiser les decks des joueurs (transfert de propriété)
    joueur1.initialiserDeck(std::move(deck1));
    joueur2.initialiserDeck(std::move(deck2));
    
    // Ajouter les joueurs à la partie
    partie.ajouterJoueur(std::move(joueur1));
    partie.ajouterJoueur(std::move(joueur2));
    
    // Piocher les mains de départ
    std::cout << "Pioche des mains de départ..." << std::endl;
    partie.getJoueurParId(0)->piocher(5);
    partie.getJoueurParId(1)->piocher(5);
    
    // Initialiser le marché
    std::cout << "Initialisation du marché..." << std::endl;
    for (int i = 0; i < 5; i++) {
        partie.ajouterCarteRiviere(creerCarteDegat("Marché Carte " + std::to_string(i), 4, 2));
    }
    
    // Tests de vérification
    std::cout << "\n=== État initial ===" << std::endl;
    std::cout << "Joueur 1:" << std::endl;
    std::cout << "  - Pioche: " << partie.getJoueurParId(0)->getPioche().size() << " cartes" << std::endl;
    std::cout << "  - Main: " << partie.getJoueurParId(0)->getMain().size() << " cartes" << std::endl;
    std::cout << "  - Or: " << partie.getJoueurParId(0)->getOr() << std::endl;
    
    std::cout << "Joueur 2:" << std::endl;
    std::cout << "  - Pioche: " << partie.getJoueurParId(1)->getPioche().size() << " cartes" << std::endl;
    std::cout << "  - Main: " << partie.getJoueurParId(1)->getMain().size() << " cartes" << std::endl;
    std::cout << "  - Or: " << partie.getJoueurParId(1)->getOr() << std::endl;
    
    std::cout << "Marché: " << partie.getRiviere().size() << " cartes" << std::endl;
    
    // Test de déplacement de carte
    std::cout << "\n=== Test de déplacement ===" << std::endl;
    auto mainJ1 = partie.getJoueurParId(0)->getMain();
    if (!mainJ1.empty()) {
        int carteId = mainJ1[0]->getId();
        std::cout << "Tentative de jouer la carte ID " << carteId << std::endl;
        
        // Donner de l'or au joueur pour qu'il puisse jouer
        partie.getJoueurParId(0)->setOr(10);
        
        if (partie.getJoueurParId(0)->jouerCarte(carteId)) {
            std::cout << "✓ Carte jouée avec succès" << std::endl;
            std::cout << "  - Main: " << partie.getJoueurParId(0)->getMain().size() << " cartes" << std::endl;
            std::cout << "  - Plateau: " << partie.getJoueurParId(0)->getPlateau().size() << " cartes" << std::endl;
        } else {
            std::cout << "✗ Échec de jouer la carte" << std::endl;
        }
    }
    
    // Lancer l'interface SFML
    std::cout << "\n=== Lancement de l'interface graphique ===" << std::endl;
    SFMLGame jeu(&partie);

    jeu.gameLoop();
    
    return 0;
}
