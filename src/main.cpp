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


int main() {
    // Créer une partie
    Partie partie = Partie();
    
    // Lancer l'interface SFML
    SFMLGame jeu(&partie);

    // Lancer la boucle de jeu
    jeu.gameLoop();
    
    return 0;
}
