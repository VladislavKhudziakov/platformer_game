//
//  MapSprite.cpp
//  platformer_game
//
//  Created by Vladislav Khudiakov on 5/19/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#include "MapSprite.hpp"

namespace GO {
  MapSprite::MapSprite() : GameObjectBase()
  {
    calculateSpriteScale();
  }
  
  
  MapSprite::MapSprite(const sf::Image& texImg) : GameObjectBase(texImg)
  {
    calculateSpriteScale();
  }
  
  
  MapSprite::MapSprite(const std::string& texName) : GameObjectBase(texName)
  {
    calculateSpriteScale();
  }
  
  
  void MapSprite::calculateSpriteScale()
  {
    updateSize();
    sf::Vector2f spriteSize = getSize();
    sf::Vector2f currScale(1., 1.);
    
    if (spriteSize.x != settings::sprite_resolution) {
      currScale.x = double(settings::sprite_resolution) / spriteSize.x;
    }
    
    if (spriteSize.y != settings::sprite_resolution) {
      currScale.y = double(settings::sprite_resolution) / spriteSize.y;
    }
    
    scale(currScale);
  }
}
