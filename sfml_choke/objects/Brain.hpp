
#ifndef Brain_hpp
#define Brain_hpp

#include "CollisionObject.hpp"
#include "GameData.hpp"
#include "gameUnit.hpp"
#include <exception>
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
    void attack(const std::vector<std::string>&);
    
    void detectPlayer(const std::vector<std::string>&);
    sf::Vector2i checkForWallsY(const std::vector<std::string>&);
    sf::Vector2i checkForWallsX(const std::vector<std::string>&);
    
  public:
    Brain(GameUnit* owner,
          settings::unitsDirections direction = settings::unitsDirections::none,
          settings::unitsMindStates mindState = settings::unitsMindStates::stand);
    
    void think(const std::vector<std::string>&);
    void handleCollisionX(const CollisionObject&);
  };
}

#endif /* Brain_hpp */
