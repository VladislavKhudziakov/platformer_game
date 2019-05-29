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
  
  
  GameUnit::GameUnit(const sf::Texture& tex, const std::string& name, float x, float y)
    : GameObjectBase(tex)
  {
    this->name = name;
    
    walkingCounter = 0;
    walkingTimer = sf::Clock();
    walkingTimer.restart();
    
    auto timer = walkingTimer.getElapsedTime();
    lastTime = timer.asMilliseconds();
    auto skinSize = getTexture()->getSize();
    
    int rectWidth =  skinSize.x / 4;
    int rectHeight = skinSize.y;
    
    sf::IntRect texRect(walkingCounter * rectWidth, 0, rectWidth, rectHeight);
    
    setTextureRect(texRect);
    
    calculateSpriteScale();
    
    sf::Vector2f scale = getScale();
    
    hitBox.top = y;
    hitBox.left = x;
    hitBox.width = rectWidth * scale.x;
    hitBox.height = rectHeight * scale.y;
    
    setPosition(hitBox.left, hitBox.top);
  }
  
  
  GameUnit::GameUnit(const std::string& texName,  const std::string& name, float x, float y)
    : GameObjectBase(texName)
  {
    this->name = name;
    
    walkingCounter = 0;
    walkingTimer = sf::Clock();
    walkingTimer.restart();
    
    auto timer = walkingTimer.getElapsedTime();
    lastTime = timer.asSeconds();
    
    
    auto skinSize = getTexture()->getSize();
    
    int rectWidth =  skinSize.x / 4;
    int rectHeight = skinSize.y;
    
    sf::IntRect texRect(walkingCounter * rectWidth, 0, rectWidth, rectHeight);
    
    setTextureRect(texRect);
    
    calculateSpriteScale();
    
    sf::Vector2f scale = getScale();
    
    hitBox.top = y;
    hitBox.left = x;
    hitBox.width = rectWidth * scale.x;
    hitBox.height = rectHeight * scale.y;
    
    setPosition(hitBox.left, hitBox.top);
  }
  
  
  GameUnit::GameUnit(GameUnit& other) : GameObjectBase(*other.getTexture())
  {
    walkingCounter = 0;
    walkingTimer = sf::Clock();
    walkingTimer.restart();
    
    auto timer = walkingTimer.getElapsedTime();
    lastTime = timer.asSeconds();
    
    setTextureRect(other.getTextureRect());
    
    hitBox.top = other.hitBox.top;
    hitBox.left = other.hitBox.left;
    hitBox.width = other.hitBox.width;
    hitBox.height = other.hitBox.height;
    
    setPosition(hitBox.left, hitBox.top);
  }
  
  
  void GameUnit::onUpdate(double delta, const std::vector<std::string>& map)
  {
    if (isJump) {
      sf::Vector2f point = getPosition();
      double jumpHeight = settings::jumpSize * settings::sprite_resolution;
      
      if (!(point.y + hitBox.height >= jumpStartY - jumpHeight)) {
        isJump = false;
      }
    }
    
    hitBox.top += dy * delta / 200;
    detectCollisionY(map);
    
    hitBox.left += dx * delta / 200;
    detectCollisionX(map);
    
    setPosition(hitBox.left, hitBox.top);
    
    dx = 0;
    
    if (!isJump) {
      dy = settings::gravityForce;
    }
  }
  
  
  void GameUnit::detectCollisionX(const std::vector<std::string>& map)
  {
    int tileSize = settings::sprite_resolution;
    
    for (int i = hitBox.top / tileSize; i < (hitBox.top + hitBox.height) / tileSize; i++) {
      for (int j = hitBox.left / tileSize; j < (hitBox.left + hitBox.width) / tileSize; j++) {
        try {
          handleCollisionX(CollisionObject(map.at(i).at(j), j, i));
        } catch (std::out_of_range) {
          std::cerr <<  "out of parameters i:" << i << "j: " << j << std::endl;
        }
      }
    }
    return CollisionObject('\0', 0, 0);
  }
  
  
  const std::string& GameUnit::getName()
  {
    return name;
  }
  
  
  void GameUnit::handleCollisionX(const CollisionObject& colObj)
  {
    if (exist(settings::walls, colObj.getLabel())) {
      int tileSize = settings::sprite_resolution;
      
      sf::Vector2i pos = colObj.getPosition();
      
      if (dx > 0) hitBox.left = pos.x * tileSize - tileSize;
      if (dx < 0) hitBox.left = pos.x * tileSize + tileSize;
    }
  }
  
  
  void GameUnit::detectCollisionY(const std::vector<std::string>& map)
  {
    int tileSize = settings::sprite_resolution;
    
    for (int i = hitBox.top / tileSize; i < (hitBox.top + hitBox.height) / tileSize; i++) {
      for (int j = hitBox.left / tileSize; j < (hitBox.left + hitBox.width) / tileSize; j++) {
        try {
          handleCollisionY(CollisionObject(map.at(i).at(j), j, i));
        } catch (std::out_of_range) {
          std::cout <<  "out of parameters i:" << i << "j: " << j << std::endl;
        }
      }
    }
    
    return CollisionObject('\0', 0, 0);
  }
  
  
  void GameUnit::handleCollisionY(const CollisionObject& colObj)
  {
    int tileSize = settings::sprite_resolution;
    
    sf::Vector2i pos = colObj.getPosition();
    
    if (exist(settings::walls, colObj.getLabel())) {
      if (dy > 0) {
        hitBox.top = pos.y * tileSize - tileSize * 2;
        onGround = true;
      } else if (dy < 0) {
        hitBox.top = pos.y * tileSize + tileSize;
        isJump = false;
      }
    } else if (exist(settings::damageObjects, colObj.getLabel())) {
      getDamage(colObj.getLabel());
    }
  }
  
  
  void GameUnit::moveLeft()
  {
    auto timer = walkingTimer.getElapsedTime();
    double now = timer.asMilliseconds();
    
    if (now >= lastTime + walkDelay) {
      walkingCounter = walkingCounter + 1 >= animSize ? 0 : walkingCounter + 1;
      
      auto skinSize = getTexture()->getSize();
      
      int rectWidth = skinSize.x / animSize;
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
    
    if (getPosition().x + hitBox.width < settings::windowWidth) {
      dx = 0.1;
    }
  }
  
  
  const sf::FloatRect& GameUnit::getHitbox()
  {
    return hitBox;
  }
  
  
  void GameUnit::jump()
  {
    if (!isJump && onGround) {
      dy = settings::jumpForce;
      jumpStartY = hitBox.top;
      onGround = false;
      isJump = true;
    }
  }
  
  
  void GameUnit::stop()
  {
    dx = 0;
  }
  
  
  void GameUnit::calculateSpriteScale()
  {
    auto r = getTextureRect();
    
    sf::Vector2f currScale(1., 1.);

    if (r.width != settings::sprite_resolution * settings::playerWidth) {
      double spriteWidth = settings::sprite_resolution * settings::playerWidth;
      currScale.x = spriteWidth / r.width;
    }

    if (r.height != settings::sprite_resolution * settings::playerHeight) {
      double spriteHeight = settings::sprite_resolution * settings::playerHeight;
      currScale.y = spriteHeight / r.height;
    }
    
    scale(currScale);
  }
  
  
  void GameUnit::getDamage(char damageObject)
  {
    if (settings::damageObjectsData.count(damageObject) > 0 && hp > 0) {
      hp -= settings::damageObjectsData.at(damageObject);
    }
    
//    std::cout << "got damage from " << damageObject << ";\n";
//    std::cout << name + " curr hp: " << hp << ";\n";
    
    if (hp <= 0) {
      hp = 0;
      std::cout << name + " died.\n";
    }
  }
  
  
  float GameUnit::getHp()
  {
    return hp;
  }
  
  
  void GameUnit::setName(const std::string& newName)
  {
    name = newName;
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
