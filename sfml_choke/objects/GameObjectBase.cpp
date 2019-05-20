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
    textureImage = sf::Image();
    skin = sf::Texture();
    node = sf::Sprite(skin);
  }
  
  
  GameObjectBase::GameObjectBase(const sf::Image& texImg)
  {
    textureImage = texImg;
    skin = sf::Texture();
    skin.loadFromImage(textureImage);
    node = sf::Sprite(skin);
  }
  
  
  GameObjectBase::GameObjectBase(const std::string& textureName)
  {
    textureImage = sf::Image();
    textureImage.loadFromFile(resourcePath() + textureName);
    skin = sf::Texture();
    skin.loadFromImage(textureImage);
    node = sf::Sprite(skin);
  }
  
  
  void GameObjectBase::scale(float scaleX, float scaleY)
  {
    node.scale(scaleX, scaleY);
    updateRect();
  }
  
  
  void GameObjectBase::scale(const sf::Vector2f& scale)
  {
    node.scale(scale);
    updateRect();
  }
  
  
  void GameObjectBase::setScale(float scaleX, float scaleY)
  {
    node.setScale(scaleX, scaleY);
    updateRect();
  }
  
  
  void GameObjectBase::setScale(const sf::Vector2f& scale)
  {
    node.setScale(scale);
    updateRect();
  }
  
  
  void GameObjectBase::move(float offsetX, float offsetY)
  {
    node.move(offsetX, offsetY);
    updateRect();
  }
  
  
  void GameObjectBase::move(const sf::Vector2f& offset)
  {
    node.move(offset);
    updateRect();
  }
  
  
  void GameObjectBase::setPosition(float x, float y)
  {
    node.setPosition(x, y);
    updateRect();
  }
  
  
  void GameObjectBase::setPosition(const sf::Vector2f& point)
  {
    node.setPosition(point);
    updateRect();
  }
  
  
  void GameObjectBase::rotate(float angle)
  {
    node.rotate(angle);
  }
  
  
  void GameObjectBase::setTexture(const sf::Image& newTexImg, bool resetRect)
  {
    textureImage = newTexImg;
    skin.loadFromImage(textureImage);
    node.setTexture(skin);
    updateRect();
  }
  
  
  void GameObjectBase::setTextureRect(const sf::IntRect& rectangle)
  {
    node.setTextureRect(rectangle);
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
  
  
  const GO::HitBox& GameObjectBase::getRect()
  {
    return rect;
  }
  
  
  const sf::Image& GameObjectBase::getTextureImage()
  {
    return textureImage;
  }
  
  
  void GameObjectBase::updateRect()
  {
    sf::IntRect size = getTextureRect();
    sf::Vector2f scale = getScale();
    double width = scale.x * size.width;
    double height = scale.y * size.height;
    sf::Vector2f position = getPosition();
    
    sf::Vector2f leftBottomVertex = sf::Vector2f(
      position.x - width / 2, position.y - height / 2);
    sf::Vector2f rightTopVertex = sf::Vector2f(
      position.x + width / 2, position.y + height / 2);

    rect.update(rightTopVertex, leftBottomVertex);
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
