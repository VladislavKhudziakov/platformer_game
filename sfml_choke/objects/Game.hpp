//
//  Game.hpp
//  sfml_choke
//
//  Created by Vladislav Khudiakov on 5/16/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <iostream>
#include <vector>

#include "gameUnit.hpp"
#include "BaseEnemy.hpp"
#include "GameData.hpp"
#include "Map.hpp"
#include "MapSprite.hpp"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "../global.h"

//extern GO::GameUnit* playerPtr;

namespace GO {
  
  class Game
  {
  private:
    sf::RenderWindow* gameWindow;
    sf::Clock timer;
    double prevFrameTime;
    
    void onUpdate();
    void inputKeysHandler();
    void assertMapBuilding();
    void renderMap();
    void renderPlayer(double, const std::vector<std::string>&);
    void renderUnit(std::shared_ptr<GO::GameUnit>, double, const std::vector<std::string>&);
    void renderUnits(double, const std::vector<std::string>&);
    
  public:
    Game();
    ~Game();
    void loadMap(const std::string&);
    void buildMap();
    void start();
    void stop();
  };
  
}


#endif /* Game_hpp */
