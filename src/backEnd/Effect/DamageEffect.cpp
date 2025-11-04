#include "backEnd/Effect/DamageEffect.hpp"
#include "backEnd/Joueur.hpp"
#include <iostream>


void DamageEffect::applyEffect(Joueur *joueur) {
    if (!joueur) {
        std::cerr << "Erreur: joueur est nullptr dans DamageEffect" << std::endl;
        return;
    }
    
    std::cout << "DamageEffect appliqué sur " << joueur->getNom() 
              << " (" << _damage << " dégâts)" << std::endl;
    
    // Appliquer les dégâts de base
    joueur->ajouterDegat(_damage);

    // Bonus selon le type d’occurrence
    switch (_occurenceType) {
        case OccurenceType::Champion: {
            for (const auto& carte : joueur->getPlateau()) {
                if (carte->estChampion()) {
                    joueur->ajouterDegat(_valueByOccurence);
                }
            }
            break;
        }

        case OccurenceType::Guard: {
            for (const auto& carte : joueur->getPlateau()) {
                if (carte->estChampion()) {
                    const Champion* champ = static_cast<const Champion*>(carte);
                    if (champ->getGardien()) {
                        joueur->ajouterDegat(_valueByOccurence);
                    }
                }
            }
            break;
        }

        case OccurenceType::CarteSauvage: {
            for (const auto& carte : joueur->getPlateau()) {
                if (carte->getFaction() == Faction::Sauvage) {
                    joueur->ajouterDegat(_valueByOccurence);
                }
            }
            break;
        }

        default:
            break;
    }}


