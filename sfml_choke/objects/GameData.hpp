
#ifndef gameData_hpp
#define gameData_hpp

#include <vector>
#include <memory>

#include "gameUnit.hpp"
#include "MapSprite.hpp"
#include "Map.hpp"

namespace GO {
  class GameUnit;
  class Map;
}

namespace GameData {
  extern std::shared_ptr<GO::GameUnit> player;
  extern std::shared_ptr<GO::Map> map;
  extern std::vector<std::shared_ptr<GO::GameUnit>> activeUnits;
  extern std::vector<std::shared_ptr<GO::MapSprite>> mapTiles;
}

#endif /* gameData_hpp */
