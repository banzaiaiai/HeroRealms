
#include "backEnd/Effect/SacrificeCard.hpp"
#include "backEnd/Carte/Champion.hpp"
#include "backEnd/Joueur.hpp"
#include "backEnd/Partie.hpp"
#include "frontEnd/Overlay.hpp"


SacrificeCard::SacrificeCard(int damageForSacrifice):
        _damageForSacrifice(damageForSacrifice) {};

void SacrificeCard::applyEffect(Joueur *joueur) {
    
    Overlay overlay;
    const Carte noneCard = Carte("None", 0, Faction::Neutre, "assets/alternative_carte/none.jpg");
    const int noneCardId = noneCard.getId();
    while (true) {
        int carteId = overlay.openOverlay("SelectChampion",
                                          joueur->getMain(),
                                          joueur->getDefausse(),
                                          std::vector<const Carte*>{&noneCard}
                                          );
        if (carteId == -1) {
            std::cerr << "Aucune carte sélectionnée pour l'engagement." << std::endl;
            continue; // Sortir si aucune carte n'est sélectionnée    
        }
        if (carteId == noneCardId) {
            break;
        }
        Carte* carteJouee = joueur->getCarteById(carteId);
        if (!carteJouee) {
            std::cerr << "Probléme de carte dans l'engagement: id introuvable sur le plateau" << std::endl;
            continue; 
        }
        joueur->getPartie()->getDefausseCommune().push_back(std::move(carteJouee));
        joueur->ajouterDegat(_damageForSacrifice);
        break;
    }
}
