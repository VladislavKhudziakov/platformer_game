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
    updateSize();
  }
  
  
  void GameObjectBase::scale(const sf::Vector2f& scale)
  {
    node.scale(scale);
    updateSize();
  }
  
  
  void GameObjectBase::setScale(float scaleX, float scaleY)
  {
    node.setScale(scaleX, scaleY);
    updateSize();
  }
  
  
  void GameObjectBase::setScale(const sf::Vector2f& scale)
  {
    node.setScale(scale);
    updateSize();
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
    updateSize();
  }
  
  
  void GameObjectBase::setTextureRect(const sf::IntRect& rectangle)
  {
    node.setTextureRect(rectangle);
    updateSize();
  }
  
  const sf::Vector2f& GameObjectBase::getPosition()
  {
    return node.getPosition();
  }
  
  
  const sf::Vector2f& GameObjectBase::getScale()
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
  
  
  const sf::IntRect& GameObjectBase::getTextureRect()
  {
    return node.getTextureRect();
  }
  
  
  const sf::Vector2f& GameObjectBase::getOrigin()
  {
    return node.getOrigin();
  }
  
  
  float GameObjectBase::getRotation()
  {
    return node.getRotation();
  }
  
  
  const sf::Sprite* GameObjectBase::getNode()
  {
    return &node;
  }
  
  
  const sf::Texture* GameObjectBase::getTexture()
  {
    return &skin;
  }
  
  
  const sf::Vector2f& GameObjectBase::getSize()
  {
    return size;
  }
  
  
  void GameObjectBase::updateSize()
  {
    sf::IntRect textureRect = getTextureRect();
    sf::Vector2f scale = getScale();
    size.y = scale.y * textureRect.height;
    size.x = scale.x * textureRect.width;
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
