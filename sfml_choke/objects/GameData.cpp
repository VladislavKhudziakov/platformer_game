
#include "GameData.hpp"

namespace GameData {
  std::shared_ptr<GO::GameUnit> player(nullptr);
  std::shared_ptr<GO::Map> map(nullptr);
  std::vector<std::shared_ptr<GO::GameUnit>> activeUnits = {};
  std::vector<std::shared_ptr<GO::MapSprite>> mapTiles = {};
}
