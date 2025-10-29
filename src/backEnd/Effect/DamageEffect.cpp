#include "backEnd/Effect/DamageEffect.hpp"
#include "backEnd/Joueur.hpp"
#include <iostream>

DamageEffect::DamageEffect(int damage) : _damage(damage) 
{
    std::cout << "DamageEffect créé avec degat " <<_damage << std::endl;
}

void DamageEffect::applyEffect(Joueur *joueur) {
    if (!joueur) {
        std::cerr << "Erreur: joueur est nullptr dans DamageEffect" << std::endl;
        return;
    }
    
    std::cout << "DamageEffect appliqué sur " << joueur->getNom() 
              << " (" << _damage << " dégâts)" << std::endl;
    
    // Appliquer les dégâts au joueur
    int degatActuelle = joueur->getDegat();
    int nouveauxDegat = degatActuelle + _damage;
    std::cout << "  degat avant: " << degatActuelle << std::endl;
    joueur->setDegat(nouveauxDegat);
    //std::cout << "  degat après: " << joueur->getDegat() << std::endl;
    
    // OU si tu veux augmenter les dégâts du joueur (attaque):
    // joueur->setDegat(joueur->getDegat() + _damage);*/
}