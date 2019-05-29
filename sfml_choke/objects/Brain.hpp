
#ifndef Brain_hpp
#define Brain_hpp

#include "CollisionObject.hpp"
#include "GameData.hpp"
#include "gameUnit.hpp"
#include "../global.h"

namespace GO {
  
  class GameUnit;
  
  class Brain
  {
  private:
    GameUnit* owner;
    settings::unitsDirections currDirection = settings::unitsDirections::none;
    settings::unitsMindStates currMindState = settings::unitsMindStates::stand;
    
  protected:
    void checkHazards(const std::vector<std::string>&);
    void checkHazardsByLeftSide(const std::vector<std::string>&);
    void checkHazardsByRightSide(const std::vector<std::string>&);
    void detectPlayer();
    void attack();
    
  public:
    Brain(GameUnit* owner,
          settings::unitsDirections direction = settings::unitsDirections::none,
          settings::unitsMindStates mindState = settings::unitsMindStates::stand);
    
    void think(const std::vector<std::string>&);
    void handleCollisionX(const CollisionObject&);
  };
}

#endif /* Brain_hpp */
