//
//  gameObject.cpp
//  sfml_choke
//
//  Created by Vladislav Khudiakov on 5/15/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#include "gameUnit.hpp"

namespace GO {
  
  GameUnit::GameUnit() : GameObjectBase()
  {
    walkingCounter = 0;
    walkingTimer = sf::Clock();
    auto timer = walkingTimer.getElapsedTime();
    lastTime = timer.asSeconds();
    
    walkingCounter = 0;
    onGround = false;
    isJump = false;
  }
  
  GameUnit::GameUnit(const sf::Texture& texture, float x, float y, float sX, float sY)
  : GameObjectBase(texture)
  {
    walkingCounter = 0;
    walkingTimer = sf::Clock();
    walkingTimer.restart();
    
    auto timer = walkingTimer.getElapsedTime();
    lastTime = timer.asSeconds();
    
    scale = sf::Vector2f(sY, sY);
    setScale(scale);
    
    auto skinSize = getTexture()->getSize();
    
    setTextureRect(
     sf::Rect<int>(
       walkingCounter * skinSize.x / 4, 0, skinSize.x / 4, skinSize.y)
   );
    
    move(x, y);
    onGround = false;
    isJump = false;
  }

  
  
  GameUnit::GameUnit(
   const std::string& texName, float x, float y, float sX, float sY)
  : GameObjectBase(texName)
  {
    walkingCounter = 0;
    walkingTimer = sf::Clock();
    walkingTimer.restart();
    
    auto timer = walkingTimer.getElapsedTime();
    lastTime = timer.asSeconds();
    
    scale = sf::Vector2f(sY, sY);
    setScale(scale);
    
    auto skinSize = getTexture()->getSize();
    
    setTextureRect(
      sf::Rect<int>(
        walkingCounter * skinSize.x / 4, 0, skinSize.x / 4, skinSize.y)
    );
    
    move(x, y);
    onGround = false;
    isJump = false;
  }
  
  
  GameUnit::GameUnit(GameUnit& other) : GameObjectBase(*other.getTexture())
  {
    walkingCounter = 0;
    walkingTimer = sf::Clock();
    walkingTimer.restart();
    
    auto timer = walkingTimer.getElapsedTime();
    lastTime = timer.asSeconds();
    
    scale = other.scale;
    GameObjectBase::setScale(scale.x, scale.y);
    
    auto skinSize = getTexture()->getSize();
    
    setTextureRect(
      sf::Rect<int>(
        walkingCounter * skinSize.x / 4, 0, skinSize.x / 4, skinSize.y)
    );
    
    move(other.getPosition());
    onGround = false;
    isJump = false;
  }
  
  
  GameUnit::~GameUnit() { }
  
  
  void GameUnit::onFall()
  {
    if (!onGround && !isJump) {
      
      auto scale = getScale();
      auto point = getPosition();
      auto size = getNode()->getTextureRect();
      size.width *= scale.x;
      size.height *= scale.y;
      
      if (point.y + size.height <= settings::windowHeiht) {
        move(0, 1.5);
      } else {
        onGround = true;
      }
    }
  }
  
  
  void GameUnit::onUpdate()
  {
    onFall();
    onJump();
  }
  
  
  void GameUnit::moveLeft()
  {
    setOrigin({ getNode()->getLocalBounds().width, 0 });
    setScale(-scale.x, scale.y);
    
    auto timer = walkingTimer.getElapsedTime();
    double now = timer.asSeconds();
    
    if (now >= lastTime + walkDelay) {
      
      walkingCounter = walkingCounter + 1 >= 4 ? 0 : walkingCounter + 1;
      
      auto skinSize = getTexture()->getSize();
      
      setTextureRect(
        sf::Rect<int>(
        walkingCounter * skinSize.x / 4,
        0, skinSize.x / 4, skinSize.y));
      
      lastTime = now;
    }
    
    auto scale = getScale();
    auto point = getPosition();
    auto size = getTextureRect();
    
    size.width *= scale.x;
    size.height *= scale.y;
    
    if (point.x > -size.width) {
      move(-1.0, 0);
    }
  }
  
  
  void GameUnit::moveRight()
  {
    setOrigin({ getNode()->getLocalBounds().width, 0 });
    setScale(scale.x, scale.y);
    
    auto timer = walkingTimer.getElapsedTime();
    double now = timer.asSeconds();
    
    if (now >= lastTime + walkDelay) {
      walkingCounter = walkingCounter + 1 >= 4 ? 0 : walkingCounter + 1;

      auto skinSize = getTexture()->getSize();

      setTextureRect(
        sf::Rect<int>(
          walkingCounter * skinSize.x / 4,
          0, skinSize.x / 4, skinSize.y));
      
      lastTime = now;
    }
    
    auto scale = getScale();
    auto point = getPosition();
    auto size = getNode()->getTextureRect();
    size.width *= scale.x;
    size.height *= scale.y;
    
    if (point.x + size.width < settings::windowWidth) {
      move(1.0, 0);
    }
    
  }
  
  
  void GameUnit::onJump()
  {
    if (isJump) {
      auto point = getPosition();
      auto size = getNode()->getTextureRect();
      
      if (point.y + size.height >= settings::windowHeiht - settings::jumpSize) {
        move(0, -3);
      } else {
        isJump = false;
      }
    }
  }
  
  
  void GameUnit::jump()
  {
    if (onGround) {
      isJump = true;
      onGround = false;
    }
  }
  
  
  GameUnit::operator sf::Sprite()
  {
    return GameObjectBase::operator sf::Sprite();
  }
  
  
  GameUnit::operator sf::Sprite*()
  {
    return GameObjectBase::operator sf::Sprite*();
  }
  
}
