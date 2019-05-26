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
  
  class GameUnit : protected GameObjectBase
  {
  private:
    float hp;
    
    int walkingCounter = 0;
    sf::Clock walkingTimer;
    float walkDelay = 250;
    
    float lastTime;
    float prevFrame;
    
    float jumpStartY = 0;
    float dy = 0.1;
    float dx = 0;
    
    bool onGround = false;
    bool isJump = false;
    sf::FloatRect hitBox;
    
  protected:
    void colX(const std::vector<std::string>&);
    void colY(const std::vector<std::string>&);
    
  public:
    GameUnit();
    GameUnit(GameUnit&);
    GameUnit(const std::string&, float x = 0, float y = 0);
    GameUnit(const sf::Texture&, float x = 0, float y = 0);
    ~GameUnit();
    void onUpdate(double, const std::vector<std::string>&);
    void jump();
    void moveLeft();
    void moveRight();
    void stop();
    void calculateSpriteScale();
    void setColor(const sf::Color&);
    const sf::FloatRect& getHitbox();
    operator sf::Sprite();
    operator sf::Sprite*();
  };
}

#endif /* gameObject_hpp */
