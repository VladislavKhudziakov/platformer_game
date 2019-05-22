//
//  global.cpp
//  platformer_game
//
//  Created by Vladislav Khudiakov on 5/22/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#include <stdio.h>

#include "global.h"

namespace settings {
  
  int windowWidth;
  int windowHeight;
  
  
  const int sprite_resolution = 32;
  const int jumpSize = 3;
  
  const sf::Keyboard::Key jumpKey = sf::Keyboard::Space;
  const sf::Keyboard::Key moveLeftKey = sf::Keyboard::A;
  const sf::Keyboard::Key moveRightKey = sf::Keyboard::D;
  const int playerHeight = 2;
  const int playerWidth = 1;
}
