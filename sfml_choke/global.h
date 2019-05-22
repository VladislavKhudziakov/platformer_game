//
//  global.h
//  sfml_choke
//
//  Created by Vladislav Khudiakov on 5/16/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#ifndef global_h
#define global_h

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

namespace settings {
  
  extern int windowWidth;
  extern int windowHeight;
  
  extern const int sprite_resolution;
  extern const int jumpSize;
  
  extern const sf::Keyboard::Key jumpKey;
  extern const sf::Keyboard::Key moveLeftKey;
  extern const sf::Keyboard::Key moveRightKey;
  extern const int playerHeight;
  extern const int playerWidth;
}

#endif /* global_h */
