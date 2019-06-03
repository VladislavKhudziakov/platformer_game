
#include "GameData.hpp"

namespace GameData {
  GO::GameUnit* player = nullptr;
  GO::Map* map = nullptr;
  std::vector<GO::GameUnit* > activeUnits = {};
  std::vector<GO::MapSprite* > mapTiles = {};
}
