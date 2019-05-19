//
//  MapSprite.cpp
//  platformer_game
//
//  Created by Vladislav Khudiakov on 5/19/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#include "MapSprite.hpp"

namespace GO {
//  class MapSprite
//  {
//  private:
//    sf::Texture skin;
//    sf::Sprite node;
//
//  public:
//    MapSprite();
//    MapSprite(const sf::Texture&);
//    MapSprite(const std::string&);
//    ~MapSprite();
//  };
  MapSprite::MapSprite()
  {
    skin = sf::Texture();
    node = sf::Sprite(skin);
  }
  
  
  MapSprite::MapSprite(const sf::Texture& texture)
  {
    skin = texture;
    node = sf::Sprite(texture);
  }
  
  
  MapSprite::MapSprite(const std::string& texName)
  {
    skin = sf::Texture();
    skin.loadFromFile(resourcePath() + texName);
    
    node = sf::Sprite();
    node.setTexture(skin);
  }
  
  
  MapSprite::~MapSprite() { }
  
  
  const sf::Sprite& MapSprite::getNode()
  {
    return node;
  }
  
  
   MapSprite::operator sf::Sprite()
  {
    return node;
  }
}
