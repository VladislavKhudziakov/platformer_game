//
//  global.cpp
//  platformer_game
//
//  Created by Vladislav Khudiakov on 5/22/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#include <stdio.h>

#include "global.h"

bool exist(const std::vector<char>& v, char c)
{
  return std::find(v.begin(), v.end(), c) != v.end();
}

namespace settings {
  
  int windowWidth;
  int windowHeight;
  
  const int sprite_resolution = 32;
  const int jumpSize = 0;
  
  const sf::Keyboard::Key jumpKey = sf::Keyboard::Space;
  const sf::Keyboard::Key moveLeftKey = sf::Keyboard::A;
  const sf::Keyboard::Key moveRightKey = sf::Keyboard::D;
  const int playerHeight = 2;
  const int playerWidth = 1;
  
  const std::map<char, sf::Vector2i> tileMap = {
    {'b', sf::Vector2i(5, 13)},
    {'B', sf::Vector2i(12, 9)},
    {'g', sf::Vector2i(7, 13)},
    {'G', sf::Vector2i(7, 12)},
    {'L', sf::Vector2i(12, 7)},
  };
  
  const std::vector<char> walls = {
    'B', 'g', 'G', 'b'
  };
}
