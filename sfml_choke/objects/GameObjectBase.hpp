//
//  GameObjectBase.hpp
//  platformer_game
//
//  Created by Vladislav Khudiakov on 5/20/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#ifndef GameObjectBase_hpp
#define GameObjectBase_hpp

#include <iostream>
#include <string>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "../ResourcePath.hpp"
#include "../global.h"


namespace GO {
  class GameObjectBase
  {
  private:
    sf::Texture skin;
    sf::Vector2f size;
    sf::Sprite node;
    
  public:
    GameObjectBase();
    GameObjectBase(const sf::Texture&);
    GameObjectBase(const std::string&);
    
    virtual void scale(float, float);
    virtual void scale(const sf::Vector2f&);
    virtual void setScale(float, float);
    virtual void setScale(const sf::Vector2f&);
    
    virtual void move(float, float);
    virtual void move(const sf::Vector2f&);
    virtual void setPosition(float, float);
    virtual void setPosition(const sf::Vector2f&);
    
    virtual void setOrigin(float x, float y);
    virtual void setOrigin(const sf::Vector2f&);
    
    virtual void setTextureRect(const sf::IntRect &);
    virtual void setTexture(const sf::Texture&, bool resetRect = false);
    
    virtual void rotate(float);
    
    virtual const sf::IntRect& getTextureRect();
    virtual const sf::Vector2f& getOrigin();
    virtual const sf::Vector2f& getPosition();
    virtual const sf::Vector2f& getScale();
    virtual const sf::Vector2f& getSize();
    
    virtual float getRotation();
    
    virtual const sf::Sprite* getNode();
    virtual const sf::Texture* getTexture();
    
    virtual void updateSize();
    
    virtual operator sf::Sprite();
    virtual operator sf::Sprite*();
  };
}
#endif /* GameObjectBase_hpp */
