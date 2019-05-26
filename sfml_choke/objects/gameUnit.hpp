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
  protected:
    float hp = settings::defaultHP;
    
    int walkingCounter = 0;
    int animSize = settings::defaultAnimationSize;
    sf::Clock walkingTimer;
    float walkDelay = settings::animDelay;
    
    float lastTime;
    float prevFrame;
    
    float jumpStartY = 0;
    float dy = settings::gravityForce;
    float dx = 0;
    
    bool onGround = false;
    bool isJump = false;
    sf::FloatRect hitBox;
    
    void colX(const std::vector<std::string>&);
    void colY(const std::vector<std::string>&);
    
  public:
    GameUnit();
    GameUnit(GameUnit&);
    GameUnit(const std::string&, float x = 0, float y = 0);
    GameUnit(const sf::Texture&, float x = 0, float y = 0);
    ~GameUnit();
    virtual void onUpdate(double, const std::vector<std::string>&);
    virtual void jump();
    virtual void moveLeft();
    virtual void moveRight();
    virtual void stop();
    virtual void calculateSpriteScale();
    virtual const sf::FloatRect& getHitbox();
    virtual operator sf::Sprite();
    virtual operator sf::Sprite*();
  };
}

#endif /* gameObject_hpp */
