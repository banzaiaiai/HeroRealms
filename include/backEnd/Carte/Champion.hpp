#ifndef CHAMPION_H
#define CHAMPION_H

#include "backEnd/Carte/Carte.hpp"


class Champion : public Carte {
private:
    int _pvTotal;
    bool _gardien;
    bool _activer;
    bool _estStun=false;

public:
    Champion(const std::string& name, int coupOr, Faction faction,
             std::string imagePath, int pvTotal, bool gardien);
    ~Champion();
    // Getters
    inline int getPvTotal() const { return _pvTotal; }
    inline bool getGardien() const { return _gardien; }
    inline bool getActiver() const { return _activer; }
    inline bool getEstStun() const { return _estStun; }

    // Setters
    inline void setPvTotal(int pvTotal) { _pvTotal = pvTotal; }
    inline void setGardien(bool gardien) { _gardien = gardien; }
    inline void setActiver(bool activer) { _activer = activer; }
    inline void setEstStun(bool estStun) { _estStun = estStun; }

    bool estChampion() const override { return true; }
    // Apply damage to the champion
    void recevoirDegat(int degat);
};

#endif // CHAMPION_H
