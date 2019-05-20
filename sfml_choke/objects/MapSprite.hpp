//
//  MapSprite.hpp
//  platformer_game
//
//  Created by Vladislav Khudiakov on 5/19/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#ifndef MapSprite_hpp
#define MapSprite_hpp

#include <iostream>
#include <string>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "../ResourcePath.hpp"
#include "../global.h"
#include "GameBlockData.h"
#include "GameObjectBase.hpp"


namespace GO {
  class MapSprite : public GameObjectBase
  {
  public:
    MapSprite() : GameObjectBase() { }
    MapSprite(const sf::Texture& texture) : GameObjectBase(texture) { }
    MapSprite(const std::string& textureName) : GameObjectBase(textureName) { }
    double calculateMapSpriteCoeff(const mapBlockData&);
    sf::Vector2f calculateSpriteScale(const mapBlockData&, double);
  };
}

#endif /* MapSprite_hpp */
