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
    lastTime = timer.asMilliseconds();
  }
  
  
  GameUnit::GameUnit(const sf::Texture& tex, float x, float y)
    : GameObjectBase(tex)
  {
    walkingCounter = 0;
    walkingTimer = sf::Clock();
    walkingTimer.restart();
    
    auto timer = walkingTimer.getElapsedTime();
    lastTime = timer.asMilliseconds();
    auto skinSize = getTexture()->getSize();
    
    int rectWidth =  skinSize.x / 4;
    int rectHeight = skinSize.y;
    
    setTextureRect(
     sf::IntRect(walkingCounter * skinSize.x / 4, 0, skinSize.x / 4, skinSize.y)
   );
    
    calculateSpriteScale();
    
    sf::Vector2f size = getSize();
    
    hitBox.top = y;
    hitBox.left = x;
    hitBox.width = size.x;
    hitBox.height = size.y;
    
    setPosition(hitBox.left, hitBox.top);
  }
  
  
  GameUnit::GameUnit(const std::string& texName, float x, float y)
    : GameObjectBase(texName)
  {
    walkingCounter = 0;
    walkingTimer = sf::Clock();
    walkingTimer.restart();
    
    auto timer = walkingTimer.getElapsedTime();
    lastTime = timer.asSeconds();
    
    
    auto skinSize = getTexture()->getSize();
    
    int rectWidth =  skinSize.x / 4;
    int rectHeight = skinSize.y;
    
    setTextureRect(
      sf::Rect<int>(
        walkingCounter * skinSize.x / 4, 0, skinSize.x / 4, skinSize.y)
    );
    
    calculateSpriteScale();
    
    sf::Vector2f size = getSize();
    
    hitBox.top = y;
    hitBox.left = x;
    hitBox.width = size.x;
    hitBox.height = size.y;

    
    setPosition(hitBox.left, hitBox.top);
  }
  
  
  GameUnit::GameUnit(GameUnit& other) : GameObjectBase(*other.getTexture())
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
  }
  
  
  GameUnit::~GameUnit() { }
  
  
  void GameUnit::onFall()
  {
    if (dy > 0) {
      
      auto scale = getScale();
      auto point = getPosition();
      auto size = getNode()->getTextureRect();
      size.width *= scale.x;
      size.height *= scale.y;
      
      if (!(point.y + size.height <= settings::windowHeight)) {
        dy = 0;
        onGround = true;
      }
    }
  }
  
  
  void GameUnit::onUpdate(double delta, const std::vector<std::string>& map)
  {
    onFall();
    onJump();
    hitBox.left += dx * delta / 200;
    colX(map);
    hitBox.top += dy * delta / 200;
    colY(map);
    
    setPosition(hitBox.left, hitBox.top);
  }
  
  void GameUnit::colX(const std::vector<std::string>& map)
  {
    int tileSize = settings::sprite_resolution;
    
    for (int i = hitBox.top / tileSize; i < (hitBox.top + hitBox.height) / tileSize; i++) {
      for (int j = hitBox.left / tileSize; j < (hitBox.left + hitBox.width) / tileSize; j++) {
        try {
          if (map.at(i).at(j) == 'b') {
            if (dx > 0) hitBox.left = j * tileSize - tileSize;
            if (dx < 0) hitBox.left = j * tileSize + tileSize;
          }
        } catch (std::out_of_range) {
          std::cout <<  "out of parameters i:" << i << "j: " << j << std::endl;
        }
      }
    }
  }
  
  
  void GameUnit::colY(const std::vector<std::string>& map)
  {
    int tileSize = settings::sprite_resolution;
    
    for (int i = hitBox.top / tileSize; i < (hitBox.top + hitBox.height) / tileSize; i++) {
      for (int j = hitBox.left / tileSize; j < (hitBox.left + hitBox.width) / tileSize; j++) {
        try {
          if (map.at(i).at(j) == 'b') {
            if (dy > 0) {
              hitBox.top = i * tileSize - tileSize * 2;
              onGround = true;
            }
            if (dy < 0) {
              hitBox.top = i * tileSize + tileSize;
            }
          }
        } catch (std::out_of_range) {
          std::cout <<  "out of parameters i:" << i << "j: " << j << std::endl;
        }
      }
    }
  }
  
  
  void GameUnit::moveLeft()
  {
    auto timer = walkingTimer.getElapsedTime();
    double now = timer.asMilliseconds();
    
    if (now >= lastTime + walkDelay) {
      walkingCounter = walkingCounter + 1 >= 4 ? 0 : walkingCounter + 1;
      
      auto skinSize = getTexture()->getSize();
      
      int rectWidth = skinSize.x / 4;
      int rectHeight = skinSize.y;
      
      setTextureRect(
        sf::IntRect(
          rectWidth * walkingCounter + rectWidth, 0, -rectWidth, rectHeight)
      );
      
      lastTime = now;
    }
    
    auto point = getPosition();
    
    if (point.x > 0) {
      dx = -0.1;
    }
  }
  
  
  void GameUnit::moveRight()
  {
    auto timer = walkingTimer.getElapsedTime();
    double now = timer.asMilliseconds();
    
    if (now >= lastTime + walkDelay) {
      walkingCounter = walkingCounter + 1 >= 4 ? 0 : walkingCounter + 1;

      auto skinSize = getTexture()->getSize();

      setTextureRect(
        sf::Rect<int>(
          walkingCounter * skinSize.x / 4, 0, skinSize.x / 4, skinSize.y));
      
      lastTime = now;
    }
    
    if (getPosition().x + getSize().x < settings::windowWidth) {
      dx = 0.1;
    }
  }
  
  const sf::FloatRect& GameUnit::getHitbox()
  {
    return hitBox;
  }
  
  
  void GameUnit::onJump()
  {
    if (!onGround && dy < 0) {
      sf::Vector2f point = getPosition();
      double jumpHeight = settings::jumpSize * settings::sprite_resolution;
      
      if (point.y + getSize().y >= jumpStartY - jumpHeight) {
        hitBox.top += dy;
      } else {
        dy = 0.1;
      }
    }
  }
  
  
  void GameUnit::moveTo(float x, float y) {
    hitBox.left = x;
    hitBox.top = y;
    move(hitBox.left, hitBox.top);
  }
  
  
  double GameUnit::getDirectionX() {
    return dx;
  }
  
  
  double GameUnit::getDirectionY() {
    return dy;
  }
  
  
  void GameUnit::getOnTheGround() {
    dy = 0;
  }
  
  void GameUnit::fall() {
    dy = 0.1;
  }
  
  
  void GameUnit::jump()
  {
    if (onGround) {
      dy = -0.1;
      jumpStartY = hitBox.top;
      onGround = false;
    }
  }
  
  
  void GameUnit::stop()
  {
    dx = 0;
  }
  
  
  void GameUnit::calculateSpriteScale()
  {
    updateSize();
    sf::Vector2f spriteSize = getSize();
    sf::Vector2f currScale(1., 1.);
    
    if (spriteSize.x != settings::sprite_resolution * settings::playerWidth) {
      double spriteWidth = settings::sprite_resolution * settings::playerWidth;
      currScale.x = spriteWidth / spriteSize.x;
    }
    
    if (spriteSize.y != settings::sprite_resolution * settings::playerHeight) {
      double spriteHeight = settings::sprite_resolution * settings::playerHeight;
      currScale.y = spriteHeight / spriteSize.y;
    }
    
    scale(currScale);
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
