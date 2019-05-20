//
//  gameObject.hpp
//  sfml_choke
//
//  Created by Vladislav Khudiakov on 5/15/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#ifndef gameUnit_hpp
#define gameUnit_hpp

#include <stdio.h>
#include <string>
#include <stdexcept>
#include "../ResourcePath.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "../global.h"

namespace GO {
  
  class GameUnit
  {
  private:
    sf::Vector2<double> scale;
    sf::Sprite node;
    sf::Texture skin;
    int walkingCounter;
    sf::Clock walkingTimer;
    float lastTime;
    float walkDelay = 0.25;
    bool onGround;
    bool isJump;

  protected:
    void onFall();
    void onJump();
    
  public:
    GameUnit();
    GameUnit(GameUnit&);
    GameUnit(std::string, float, float, float sX = 1.0, float sY = 1.0);
    ~GameUnit();
    void onUpdate();
    void jump();
    void moveLeft();
    void moveRight();
    void setColor(const sf::Color&);
    operator sf::Sprite();
  };
}

#endif /* gameObject_hpp */
