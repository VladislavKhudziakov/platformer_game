//
//  gameObject.hpp
//  sfml_choke
//
//  Created by Vladislav Khudiakov on 5/15/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#ifndef gameUnit_hpp
#define gameUnit_hpp

#include "../global.h"

#include <string>
#include <stdexcept>
#include "../ResourcePath.hpp"

#include "Brain.hpp"

#include "GameObjectBase.hpp"
#include "CollisionObject.hpp"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

namespace GO {
  
//  class Brain;
  
  class GameUnit : protected GameObjectBase
  {
  private:
    void calculateSpriteScale();
    void kill();
    
  protected:
    float hp = settings::defaultHP;
    std::string name;
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
    virtual void detectCollisionX();
    virtual void detectCollisionY();
    virtual void handleCollisionX(const CollisionObject& );
    virtual void handleCollisionY(const CollisionObject& );
    friend class Brain;
    
  public:
    GameUnit();
    GameUnit(GameUnit&);
    GameUnit(const std::string&, const std::string&, float x = 0, float y = 0);
    GameUnit(const sf::Texture&, const std::string&, float x = 0, float y = 0);
    virtual ~GameUnit() { };
    virtual void onUpdate(double);
    virtual void jump();
    virtual void moveLeft();
    virtual void moveRight();
    virtual void getDamage(char);
    virtual float getHp();
    
    virtual void stop();
    virtual void setName(const std::string&);
    virtual const std::string& getName();
    virtual const sf::FloatRect& getHitbox();
    virtual operator sf::Sprite();
    virtual operator sf::Sprite*();
  };
}

#endif /* gameObject_hpp */
