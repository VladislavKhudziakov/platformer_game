//
//  global.h
//  platformer_game
//
//  Created by Vladislav Khudiakov on 5/23/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#ifndef global_h
#define global_h
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>

bool exist(const std::vector<char>&, char);

namespace settings {
  
  extern int windowWidth;
  extern int windowHeight;
  
  extern const int sprite_resolution;
  extern const int jumpSize;
  extern const float gravityForce;
  extern const float jumpForce;
  extern const float animDelay;
  extern const float defaultAnimationSize;
  
  extern const float defaultHP;
  
  extern const sf::Keyboard::Key jumpKey;
  extern const sf::Keyboard::Key moveLeftKey;
  extern const sf::Keyboard::Key moveRightKey;
  extern const int playerHeight;
  extern const int playerWidth;
  
  extern const std::map<char, sf::Vector2i> tileMap;
  extern const std::vector<char> walls;
  
  extern const std::map<char, float> damageObjectsData;
  extern const std::vector<char> damageObjects;
  
  enum class unitsDirections : int { none, left, right };
  enum class unitsMindStates : int { attack, patrol, stand };
}

#endif /* global_h */
