
#ifndef gameData_hpp
#define gameData_hpp

#include <vector>

#include "gameUnit.hpp"
#include "MapSprite.hpp"
#include "Map.hpp"

namespace GO {
  class GameUnit;
  class Map;
}

namespace GameData {
  extern GO::GameUnit* player;
  extern GO::Map* map;
  extern std::vector<GO::GameUnit* > activeUnits;
  extern std::vector<GO::MapSprite* > mapTiles;
}

#endif /* gameData_hpp */
