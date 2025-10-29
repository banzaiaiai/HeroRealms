#ifndef IEFFECT_H
#define IEFFECT_H

class Joueur;
class Partie;

/**
 * Interface pour tous les effets de cartes
 * Les effets peuvent affecter:
 * - Le joueur qui joue la carte (cible = joueur passé en paramètre)
 * - L'adversaire (à récupérer via la partie)
 * - La partie elle-même (marché, etc.)
 */
class IEffect {
public:
    IEffect() {};
    virtual ~IEffect() = default;
    
    /**
     * Applique l'effet sur un joueur cible
     * @param joueur Le joueur affecté par l'effet
     */
    virtual void applyEffect(Joueur* joueur) = 0;
    
    /**
     * Optionnel: Applique l'effet avec contexte complet
     * @param joueur Le joueur qui joue la carte
     * @param partie La partie en cours (pour accéder aux adversaires, etc.)
     */
    virtual void applyEffect(Joueur* joueur, Partie* partie) {
        // Par défaut, appelle la version simple
        applyEffect(joueur);
    }
};

#endif // IEFFECT_H