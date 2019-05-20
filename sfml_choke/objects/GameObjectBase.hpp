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
#include "GameBlockData.h"


namespace GO {
  class GameObjectBase
  {
  private:
    sf::Texture skin;
    sf::Sprite node;
    
  public:
    GameObjectBase();
    GameObjectBase(const sf::Texture&);
    GameObjectBase(const std::string&);
    void scale(float, float);
    void scale(const sf::Vector2f&);
    void setScale(float, float);
    void setScale(const sf::Vector2f&);
    void move(float, float);
    void move(const sf::Vector2f&);
    void setPosition(float, float);
    void setPosition(const sf::Vector2f&);
    void rotate(float);
    const sf::Vector2f& getPosition();
    const sf::Vector2f& getScale();
    float getRotation();
    const sf::Sprite* getNode();
    const sf::Texture* getTexture();
    operator sf::Sprite();
    operator sf::Sprite*();
  };
}
#endif /* GameObjectBase_hpp */
