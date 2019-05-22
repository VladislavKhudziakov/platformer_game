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
  private:
    void calculateSpriteScale();
    
  public:
    MapSprite();
    MapSprite(const sf::Image& texImg);
    MapSprite(const std::string& textureName);
  };
}

#endif /* MapSprite_hpp */
