#ifndef NEXTCARDRECUP_H
#define NEXTCARDRECUP_H

#include "backEnd/Effect/IEffect.hpp"
#include "backEnd/Joueur.hpp"

class NextCardRecup : public IEffect {
private:
    int _count;
    TypeCarte _typecarte;
    ZoneType _zone;

public:
    NextCardRecup(int count=0,TypeCarte typecarte=TypeCarte::Tous, ZoneType zone=ZoneType::Main);
    ~NextCardRecup();
    void applyEffect(Joueur *joueur) override;

    // Getters
    inline int getCount() const { return _count; }

    // Setters
    inline void setCount(int count) { _count = count; }
};

#endif // NEXTCARDRECUP_H
