//
//  MapSprite.cpp
//  platformer_game
//
//  Created by Vladislav Khudiakov on 5/19/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#include "MapSprite.hpp"

namespace GO {
  MapSprite::MapSprite() : GameObjectBase() { }
  
  MapSprite::MapSprite(const sf::Texture& texture) : GameObjectBase(texture) { }
  
  MapSprite::MapSprite(const std::string& texName) : GameObjectBase(texName) { }
  
  
  void MapSprite::calculateSpriteScale()
  {
    sf::Vector2f currScale(1., 1.);
    
    sf::IntRect texRect = getTextureRect();
    
    if (texRect.width != settings::sprite_resolution) {
      currScale.x = double(settings::sprite_resolution) / texRect.width;
    }
    
    if (texRect.height != settings::sprite_resolution) {
      currScale.y = double(settings::sprite_resolution) / texRect.height;
    }
    
    scale(currScale);
  }
}
