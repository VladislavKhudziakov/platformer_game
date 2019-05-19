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


namespace GO {
  class MapSprite : public sf::Sprite
  {
  private:
    sf::Texture skin;
    
  public:
    MapSprite();
    MapSprite(const sf::Texture&);
    MapSprite(const sf::Texture&, const sf::IntRect&);
    MapSprite(const std::string&);
    double calculateMapSpriteCoeff(const mapBlockData&);
    sf::Vector2f calculateSpriteScale(const mapBlockData&, double);    
  };
}

#endif /* MapSprite_hpp */
