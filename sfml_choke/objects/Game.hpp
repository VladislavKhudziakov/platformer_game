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
#include "Map.hpp"
#include "MapSprite.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "../global.h"

namespace GO {
  
  class Game
  {
  private:
    sf::RenderWindow* gameWindow;
    GO::GameUnit* player;
    GO::Map map;
    sf::Clock timer;
    double prevFrameTime;
    std::vector<GO::MapSprite* > tiles;
    std::vector<GO::GameUnit* > units;
    
    void onUpdate();
    void inputKeysHandler();
    void assertMapBuilding();
    void renderMap();
    void renderPlayer(double, const std::vector<std::string>&);
    void renderUnit(GO::GameUnit*, double, const std::vector<std::string>&);
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
