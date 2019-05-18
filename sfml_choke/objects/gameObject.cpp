//
//  gameObject.cpp
//  sfml_choke
//
//  Created by Vladislav Khudiakov on 5/15/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#include "gameObject.hpp"
#include <iostream>

namespace GO {
  
  GameObject::GameObject()
  {
    walkingCounter = 0;
    walkingTimer = sf::Clock();
    auto timer = walkingTimer.getElapsedTime();
    lastTime = timer.asSeconds();
    
    walkingCounter = 0;
    skin = sf::Texture();
    node = sf::Sprite();
    onGround = false;
    isJump = false;
  }
  
  
  GameObject::GameObject(std::string texName, float x, float y, float sX, float sY)
  {
    walkingCounter = 0;
    walkingTimer = sf::Clock();
    walkingTimer.restart();
    
    auto timer = walkingTimer.getElapsedTime();
    lastTime = timer.asSeconds();
    
    skin = sf::Texture();
    skin.loadFromFile(resourcePath() + texName);
    
    node = sf::Sprite();
    node.setTexture(skin);
    
    scale = sf::Vector2<double>(sY, sY);
    node.setScale(scale.x, scale.y);
    
    auto skinSize = skin.getSize();
    
    node.setTextureRect(
      sf::Rect<int>(
        walkingCounter * skinSize.x / 4, 0, skinSize.x / 4, skinSize.y)
    );
    
    node.move(sf::Vector2<float>(x, y));
    onGround = false;
    isJump = false;
  }
  
  
  GameObject::GameObject(GameObject& other)
  {
    walkingCounter = 0;
    walkingTimer = sf::Clock();
    walkingTimer.restart();
    
    auto timer = walkingTimer.getElapsedTime();
    lastTime = timer.asSeconds();
    
    skin = other.skin;
    node = other.node;
    node.setTexture(skin);
    
    scale = other.scale;
    node.setScale(scale.x, scale.y);
    
    auto skinSize = skin.getSize();
    
    node.setTextureRect(
      sf::Rect<int>(
        walkingCounter * skinSize.x / 4, 0, skinSize.x / 4, skinSize.y)
    );
    
    node.move(other.node.getPosition());
    onGround = false;
    isJump = false;
  }
  
  
  GameObject::~GameObject() { }
  
  
  void GameObject::onFall()
  {
    if (!onGround && !isJump) {
      
      auto scale = node.getScale();
      auto point = node.getPosition();
      auto size = node.getTextureRect();
      size.width *= scale.x;
      size.height *= scale.y;
      
      if (point.y + size.height <= settings::windowHeiht) {
        node.move(0, 1.5);
      } else {
        onGround = true;
      }
    }
  }
  
  
  void GameObject::onUpdate()
  {
    onFall();
    onJump();
  }
  
  
  void GameObject::moveLeft()
  {
    node.setScale(-scale.x, scale.y);
    
    auto timer = walkingTimer.getElapsedTime();
    double now = timer.asSeconds();
    
    if (now >= lastTime + walkDelay) {
      
      walkingCounter = walkingCounter + 1 >= 4 ? 0 : walkingCounter + 1;
      
      auto skinSize = skin.getSize();
      
      node.setTextureRect(
        sf::Rect<int>(
        walkingCounter * skinSize.x / 4,
        0, skinSize.x / 4, skinSize.y));
      
      lastTime = now;
    }
    
    auto scale = node.getScale();
    auto point = node.getPosition();
    auto size = node.getTextureRect();
    
    size.width *= scale.x;
    size.height *= scale.y;
    
    if (point.x > -size.width) {
      node.move(-1.0, 0);
    }
  }
  
  
  void GameObject::moveRight()
  {
    node.setScale(scale.x, scale.y);
    
    auto timer = walkingTimer.getElapsedTime();
    double now = timer.asSeconds();
    
    if (now >= lastTime + walkDelay) {
      walkingCounter = walkingCounter + 1 >= 4 ? 0 : walkingCounter + 1;

      auto skinSize = skin.getSize();

      node.setTextureRect(
        sf::Rect<int>(
          walkingCounter * skinSize.x / 4,
          0, skinSize.x / 4, skinSize.y));
      
      lastTime = now;
    }
    
    auto scale = node.getScale();
    auto point = node.getPosition();
    auto size = node.getTextureRect();
    size.width *= scale.x;
    size.height *= scale.y;
    
    if (point.x + size.width < settings::windowWidth) {
      node.move(1.0, 0);
    }
    
  }
  
  
  void GameObject::onJump()
  {
    if (isJump) {
      auto point = node.getPosition();
      auto size = node.getTextureRect();
      
      if (point.y + size.height >= settings::windowHeiht - 200) {
        node.move(0, -3);
      } else {
        isJump  = false;
      }
    }
  }
  
  
  void GameObject::jump()
  {
    if (onGround) {
      isJump = true;
      onGround = false;
    }
  }
  
  
  sf::Sprite* GameObject::getNode()
  {
    return &node;
  }
  
  
  GameObject::operator sf::Sprite()
  {
    return node;
  }
  
}
