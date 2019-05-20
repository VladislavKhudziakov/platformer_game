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
  
  
  const sf::Vector2f& HitBox::getLeftBottomVertex()
  {
    return LB;
  }
  
  
   const sf::Vector2f& HitBox::getRightTopVertex()
  {
    return RT;
  }
  
  
  bool operator==(const GO::HitBox& self, const GO::HitBox& other)
  {
    if(((self.RT.x > other.LB.x && self.LB.x < other.RT.x)) &&
       (self.RT.y > other.LB.y && self.LB.y < other.RT.y)) {
      return true;
    } else {
      return false;
    }
  }
  
  
  bool operator!=(const GO::HitBox& self, const GO::HitBox& other)
  {
    if(!((self.RT.x > other.LB.x && self.LB.x < other.RT.x)) &&
       (self.RT.y > other.LB.y && self.LB.y < other.RT.y)) {
      return true;
    } else {
      return false;
    }
  }}
