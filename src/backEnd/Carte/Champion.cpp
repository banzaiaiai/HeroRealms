#include "backEnd/Carte/Champion.hpp"

Champion::Champion(const std::string& name, int coupOr, Faction faction,
             std::string imagePath, int pvTotal, bool gardien)
    : Carte(name, coupOr, faction, imagePath),
      _pvTotal(pvTotal), _gardien(gardien), _activer(false) {};

Champion::~Champion() {}
