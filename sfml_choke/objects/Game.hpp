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
#include "gameObject.hpp"
#include "Map.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "../global.h"

namespace GO {
  class Game
  {
  private:
    struct mapBlockData {
      int width;
      int height;
      int columnsCount;
      int linesCount;
    };
    
    sf::RenderWindow* gameWindow;
    GO::GameObject* player;
    GO::Map map;
    std::vector<sf::RectangleShape*> mapObjects;
    
    void onUpdate();
    void inputKeysHandler();
    mapBlockData calculateBlockSize();
    void assertMapBuilding();
    void renderMap();
    
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
