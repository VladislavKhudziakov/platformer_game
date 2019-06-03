
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
    
  protected:
    void checkHazards();
    void checkHazardsByLeftSide();
    void checkHazardsByRightSide();
    void attack();
    bool isInDanger();
    
    bool playerDetected();
    sf::Vector2i checkForWallsY();
    sf::Vector2i checkForWallsX();
    
  public:
    Brain(GameUnit* owner,
          settings::unitsDirections direction = settings::unitsDirections::none);
    
    void think();
    void handleCollisionX(const CollisionObject&);
  };
}

#endif /* Brain_hpp */
