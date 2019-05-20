//
//  HitBox.cpp
//  platformer_game
//
//  Created by Vladislav Khudiakov on 5/20/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#include "HitBox.hpp"

namespace GO {
  
  HitBox::HitBox()
  {
    LB = sf::Vector2f(0, 0);
    RT = sf::Vector2f(0, 0);
  }
  
  
  HitBox::HitBox(const sf::Vector2f& rt, const sf::Vector2f& lb)
  {
    LB = lb;
    RT = rt;
  }
  
  
  void HitBox::update(const sf::Vector2f& rt, const sf::Vector2f& lb)
  {
    LB = lb;
    RT = rt;
  }
  
  
  bool HitBox::operator==(const GO::HitBox& other)
  {
    if(((RT.x > other.LB.x && LB.x < other.RT.x)) &&
       (RT.y > other.LB.y && LB.y < other.RT.y)) {
      return true;
    } else {
      return false;
    }
  }
  
  
  bool HitBox::operator!=(const GO::HitBox& other)
  {
    if(!((RT.x > other.LB.x && LB.x < other.RT.x)) &&
       (RT.y > other.LB.y && LB.y < other.RT.y)) {
      return true;
    } else {
      return false;
    }
  }
}
