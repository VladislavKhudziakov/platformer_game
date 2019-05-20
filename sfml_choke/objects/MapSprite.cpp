//
//  MapSprite.cpp
//  platformer_game
//
//  Created by Vladislav Khudiakov on 5/19/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#include "MapSprite.hpp"

namespace GO {
  
  double MapSprite::calculateMapSpriteCoeff(const mapBlockData& blockData)
  {
    if (blockData.width >= blockData.height) {
      return  blockData.height / blockData.width;
    } else {
      return blockData.width / blockData.height;
    }
  }


  sf::Vector2f MapSprite::calculateSpriteScale(
     const mapBlockData& blockData, double sizeCoeff)
  {
    if (blockData.width >= blockData.height) {

      sf::Vector2f spriteSize(
        blockData.width * sizeCoeff, blockData.height);

      auto textureSize = GameObjectBase::getTexture()->getSize();

      return sf::Vector2f(
        spriteSize.x / textureSize.x, spriteSize.y / textureSize.y);

    } else {
      sf::Vector2f spriteSize(
        blockData.width, blockData.height * sizeCoeff);

      auto textureSize = GameObjectBase::getTexture()->getSize();

      return sf::Vector2f(
        spriteSize.x / textureSize.x, spriteSize.y / textureSize.y);
    }
  }
}
