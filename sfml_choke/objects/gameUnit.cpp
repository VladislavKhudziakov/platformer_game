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
  
  
  GameUnit::GameUnit(const sf::Image& texture, float x, float y, float sX, float sY)
  : GameObjectBase(texture)
  {
    walkingCounter = 0;
    walkingTimer = sf::Clock();
    walkingTimer.restart();
    
    auto timer = walkingTimer.getElapsedTime();
    lastTime = timer.asSeconds();
    
    auto skinSize = getTexture()->getSize();
    
    setTextureRect(
     sf::Rect<int>(
       walkingCounter * skinSize.x / 4, 0, skinSize.x / 4, skinSize.y)
   );
    
    calculateSpriteScale();
    
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
    
    
    auto skinSize = getTexture()->getSize();
    
    setTextureRect(
      sf::Rect<int>(
        walkingCounter * skinSize.x / 4, 0, skinSize.x / 4, skinSize.y)
    );
    
    calculateSpriteScale();
    
    move(x, y);
    onGround = false;
    isJump = false;
  }
  
  
  GameUnit::GameUnit(GameUnit& other) : GameObjectBase(other.getTextureImage())
  {
    walkingCounter = 0;
    walkingTimer = sf::Clock();
    walkingTimer.restart();
    
    auto timer = walkingTimer.getElapsedTime();
    lastTime = timer.asSeconds();
    
    
    auto skinSize = getTexture()->getSize();
    
    setTextureRect(
      sf::Rect<int>(
        walkingCounter * skinSize.x / 4, 0, skinSize.x / 4, skinSize.y)
    );
    
    calculateSpriteScale();
    
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
      
      if (point.y + size.height <= settings::windowHeight) {
        move(0, 0.05);
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
    if (moveDirection != right) {
      sf::Image texImage = getTextureImage();
      
      if (moveDirection == left) {
        texImage.flipHorizontally();
      }
      
      moveDirection = right;
      
      setTexture(texImage);
    }
    
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
    
    auto point = getPosition();
    
    if (point.x > 0) {
      move(-0.3, 0);
    }
  }
  
  
  void GameUnit::moveRight()
  {
    if (moveDirection != left) {
      
      sf::Image texImage = getTextureImage();
      
      if (moveDirection == right) {
        texImage.flipHorizontally();
      }
      
      moveDirection = left;
      
      setTexture(texImage);
    }
    
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
    
    if (getPosition().x + getSize().x < settings::windowWidth) {
      move(0.3, 0);
    }
    
  }
  
  
  void GameUnit::onJump()
  {
    if (isJump) {
      auto point = getPosition();
      
      if (point.y + getSize().x >= settings::windowHeight - settings::jumpSize * settings::sprite_resolution) {
        move(0, -0.1);
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
  
//
//  void GameUnit::interruptJump()
//  {
//    if (isJump) {
//      isJump = false;
//    }
//  }
//
//
//  void GameUnit::getOnTheGround()
//  {
//    if (!onGround) {
//      onGround = true;
//    }
//  }
  
  void GameUnit::calculateSpriteScale()
  {
    updateSize();
    sf::Vector2f spriteSize = getSize();
    sf::Vector2f currScale(1., 1.);
    
    if (spriteSize.x != settings::sprite_resolution * settings::playerWidth) {
      currScale.x = double(settings::sprite_resolution * settings::playerWidth) / spriteSize.x;
    }
    
    if (spriteSize.y != settings::sprite_resolution * settings::playerHeight) {
      currScale.y = double(settings::sprite_resolution * settings::playerHeight) / spriteSize.y;
    }
    
    scale(currScale);
  }
  
  void GameUnit::fall()
  {
    if (onGround) {
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
