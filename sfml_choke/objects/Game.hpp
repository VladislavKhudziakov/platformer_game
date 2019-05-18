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
#include "gameObject.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "../global.h"

namespace GO {
  class Game
  {
  private:
    sf::RenderWindow* gameWindow;
    GO::GameObject* player;
    void onUpdate();
    void inputKeysHandler();
    
  public:
    Game();
    ~Game();
    void start();
    void stop();
  };
}


#endif /* Game_hpp */
