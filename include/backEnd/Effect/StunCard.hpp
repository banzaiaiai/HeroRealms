#ifndef STUNCARD_H
#define STUNCARD_H

#include "backEnd/Effect/IEffect.hpp"
#include "backEnd/Joueur.hpp"

class StunCard : public IEffect {
private:
    int _duration;

public:
    StunCard(int duration=0);
    ~StunCard();
    void applyEffect(Joueur *joueur) override;

    // Getters
    inline int getDuration() const { return _duration; }

    // Setters
    inline void setDuration(int duration) { _duration = duration; }
};

#endif // STUNCARD_H
