
#ifndef gameData_hpp
#define gameData_hpp

#include <vector>
#include <memory>

#include "gameUnit.hpp"
#include "MapSprite.hpp"
#include "Map.hpp"
#include "Ammunition.hpp"

namespace GO {
  class GameUnit;
  class Map;
  class Ammunition;
}

namespace GameData {
  extern std::shared_ptr<GO::GameUnit> player;
  extern std::shared_ptr<GO::Map> map;
  extern std::vector<std::shared_ptr<GO::GameUnit>> activeUnits;
  extern std::vector<std::shared_ptr<GO::MapSprite>> mapTiles;
  extern std::vector<std::shared_ptr<GO::Ammunition>> activeAmmoInScene;
}

#endif /* gameData_hpp */
