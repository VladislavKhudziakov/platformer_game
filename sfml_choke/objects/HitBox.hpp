//
//  HitBox.hpp
//  platformer_game
//
//  Created by Vladislav Khudiakov on 5/20/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#ifndef HitBox_hpp
#define HitBox_hpp

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

namespace GO {
  class HitBox{
  private:
    sf::Vector2f LB;
    sf::Vector2f RT;
    
    
  public:
    HitBox();
    HitBox(const sf::Vector2f&, const sf::Vector2f&);
    void update(const sf::Vector2f&, const sf::Vector2f&);
//    bool operator==(const GO::HitBox& other);
//    bool operator!=(const GO::HitBox& other);
    bool friend operator==(const GO::HitBox& self, const GO::HitBox& other);
    bool friend operator!=(const GO::HitBox& self, const GO::HitBox& other);
  };
}

#endif /* HitBox_hpp */
