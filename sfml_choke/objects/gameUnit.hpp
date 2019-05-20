//
//  gameObject.hpp
//  sfml_choke
//
//  Created by Vladislav Khudiakov on 5/15/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#ifndef gameUnit_hpp
#define gameUnit_hpp

#include <string>
#include <stdexcept>
#include "../ResourcePath.hpp"
#include "GameObjectBase.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "../global.h"

namespace GO {
  
  class GameUnit : public GameObjectBase
  {
  private:
    sf::Vector2f scale;
    int walkingCounter;
    sf::Clock walkingTimer;
    float lastTime;
    float walkDelay = 0.25;
    bool onGround;
    bool isJump;
    enum directions {none, left, right};
    int moveDirection;
    int blockWall;

  protected:
    void onFall();
    void onJump();
    
  public:
    GameUnit();
    GameUnit(GameUnit&);
    GameUnit(const std::string&, float x = 0, float y = 0, float sX = 1.0, float sY = 1.0);
    GameUnit(const sf::Image&, float x = 0, float y = 0, float sX = 1.0, float sY = 1.0);
    ~GameUnit();
    void onUpdate();
    void jump();
    void interruptJump();
    void getOnTheGround();
    void fall();
    void setBlockWallLeft();
    void setBlockWallRight();
    void restBlockWall();
    void moveLeft();
    void moveRight();
    void setColor(const sf::Color&);
    operator sf::Sprite();
    operator sf::Sprite*();
  };
}

#endif /* gameObject_hpp */
