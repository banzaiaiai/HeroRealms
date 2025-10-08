#ifndef GODMODE_H
#define GODMODE_H

#include "backEnd/Joueur.hpp"

class Godmode : public Joueur {
public:
    Godmode();
    ~Godmode();

    void methodeBroken();
};

#endif // GODMODE_H
