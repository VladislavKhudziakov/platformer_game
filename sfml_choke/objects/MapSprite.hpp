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

namespace GO {
  class MapSprite
  {
  private:
    sf::Texture skin;
    sf::Sprite node;
    
  public:
    MapSprite();
    MapSprite(const sf::Texture&);
    MapSprite(const std::string&);
    ~MapSprite();
    const sf::Sprite& getNode();
    operator sf::Sprite();
  };
}

#endif /* MapSprite_hpp */
