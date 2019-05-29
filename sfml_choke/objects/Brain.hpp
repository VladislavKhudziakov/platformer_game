
#ifndef Brain_hpp
#define Brain_hpp

//#include "Game.hpp"
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
    enum mindStates {attack, patrol, stand};
    int currMindState;
    
  protected:
    void checkHazards(const std::vector<std::string>&);
    void checkHazardsByLeftSide(const std::vector<std::string>&);
    void checkHazardsByRightSide(const std::vector<std::string>&);
    void handleCollision();
    void detectPlayer();
    
  public:
    Brain(GameUnit* owner);
    void think(const std::vector<std::string>&);
  };
}

#endif /* Brain_hpp */
