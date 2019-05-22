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
  static int sprite_resolution = 32;
  static int windowWidth = 2560;
  static int windowHeiht = 1500;
  static int jumpSize = 200;
  
  static sf::Keyboard::Key jumpKey = sf::Keyboard::Space;
  static sf::Keyboard::Key moveLeftKey = sf::Keyboard::A;
  static sf::Keyboard::Key moveRightKey = sf::Keyboard::D;
}

#endif /* global_h */
