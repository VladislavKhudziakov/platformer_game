//
//  GameObjectBase.cpp
//  platformer_game
//
//  Created by Vladislav Khudiakov on 5/20/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#include "GameObjectBase.hpp"

namespace GO {
  
  GameObjectBase::GameObjectBase()
  {
    skin = sf::Texture();
    node = sf::Sprite(skin);
  }
  
  
  GameObjectBase::GameObjectBase(const sf::Texture& texture)
  {
    skin = texture;
    node = sf::Sprite(skin);
  }
  
  
  GameObjectBase::GameObjectBase(const std::string& textureName)
  {
    
    skin = sf::Texture();
    skin.loadFromFile(resourcePath() + textureName);
    node = sf::Sprite(skin);
  }
  
  
  void GameObjectBase::scale(float scaleX, float scaleY)
  {
    node.scale(scaleX, scaleY);
  }
  
  
  void GameObjectBase::scale(const sf::Vector2f& scale)
  {
    node.scale(scale);
  }
  
  
  void GameObjectBase::setScale(float scaleX, float scaleY)
  {
    node.setScale(scaleX, scaleY);
  }
  
  
  void GameObjectBase::setScale(const sf::Vector2f& scale)
  {
    node.setScale(scale);
  }
  
  
  void GameObjectBase::move(float offsetX, float offsetY)
  {
    node.move(offsetX, offsetY);
  }
  
  
  void GameObjectBase::move(const sf::Vector2f& offset)
  {
    node.move(offset);
  }
  
  
  void GameObjectBase::setPosition(float x, float y)
  {
    node.setPosition(x, y);
  }
  
  
  void GameObjectBase::setPosition(const sf::Vector2f& point)
  {
    node.setPosition(point);
  }
  
  
  void GameObjectBase::rotate(float angle)
  {
    node.rotate(angle);
  }
  
  
  void GameObjectBase::setTexture(const sf::Texture& newTex, bool resetRect)
  {
    skin = newTex;
    node.setTexture(skin);
  }
  
  
  void GameObjectBase::setTextureRect(const sf::IntRect& rectangle)
  {
    node.setTextureRect(rectangle);
  }
  
  const sf::Vector2f& GameObjectBase::getPosition() const
  {
    return node.getPosition();
  }
  
  
  const sf::Vector2f& GameObjectBase::getScale() const
  {
    return node.getScale();
  }
  

  void GameObjectBase::setOrigin(float x, float y)
  {
    node.setOrigin(x, y);
  }
  
  
  void GameObjectBase::setOrigin(const sf::Vector2f& origin)
  {
    node.setOrigin(origin);
  }
  
  
  const sf::IntRect& GameObjectBase::getTextureRect() const
  {
    return node.getTextureRect();
  }
  
  
  const sf::Vector2f& GameObjectBase::getOrigin() const
  {
    return node.getOrigin();
  }
  
  
  float GameObjectBase::getRotation() const
  {
    return node.getRotation();
  }
  
  
  const sf::Sprite* GameObjectBase::getNode() const
  {
    return &node;
  }
  
  
  const sf::Texture* GameObjectBase::getTexture() const
  {
    return &skin;
  }
  
  
  GameObjectBase::operator sf::Sprite()
  {
    return node;
  }
  
  
  GameObjectBase::operator sf::Sprite*()
  {
    return &node;
  }
}
