#ifndef CHAMPION_H
#define CHAMPION_H

#include "backEnd/Carte/Carte.hpp"


class Champion : public Carte {
private:
    int _pvActuel;
    int _pvTotal;
    bool _gardien;
    bool _activer;

public:
    Champion();
    ~Champion();
    // Getters
    inline int getPvActuel() const { return _pvActuel; }
    inline int getPvTotal() const { return _pvTotal; }
    inline bool getGardien() const { return _gardien; }
    inline bool getActiver() const { return _activer; }

    // Setters
    inline void setPvActuel(int pvActuel) { _pvActuel = pvActuel; }
    inline void setPvTotal(int pvTotal) { _pvTotal = pvTotal; }
    inline void setGardien(bool gardien) { _gardien = gardien; }
    inline void setActiver(bool activer) { _activer = activer; }
};

#endif // CHAMPION_H
