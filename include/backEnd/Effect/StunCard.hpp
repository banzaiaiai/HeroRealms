#ifndef STUNCARD_H
#define STUNCARD_H

#include "backEnd/Effect/IEffect.hpp"

class StunCard : public IEffect {
private:
    int _duration;

public:
    StunCard(int duration=0);
    ~StunCard();
    void applyEffect(Partie *partie) override;

    // Getters
    inline int getDuration() const { return _duration; }

    // Setters
    inline void setDuration(int duration) { _duration = duration; }
};

#endif // STUNCARD_H
