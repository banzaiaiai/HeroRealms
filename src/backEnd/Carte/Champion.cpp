#include "backEnd/Carte/Champion.hpp"

Champion::Champion(const std::string& name, int coupOr, Faction faction,
             std::string imagePath, int pvTotal, bool gardien)
    : Carte(name, coupOr, faction, imagePath),
      _pvTotal(pvTotal), _gardien(gardien), _activer(false) {};

Champion::~Champion() {}

void Champion::recevoirDegat(int degat) {
  _pvTotal -= degat;
  if (_pvTotal < 0) _pvTotal = 0;
  std::cout << "Champion " << getName() << " reçoit " << degat << " dégâts (PV restants: " << _pvTotal << ")" << std::endl;
}
