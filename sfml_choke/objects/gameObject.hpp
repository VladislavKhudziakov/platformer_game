//
//  gameObject.hpp
//  sfml_choke
//
//  Created by Vladislav Khudiakov on 5/15/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#ifndef gameObject_hpp
#define gameObject_hpp

#include <stdio.h>
#include <string>
#include "../ResourcePath.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "../global.h"

namespace GO {
  
  class GameObject
  {
  private:
    sf::Vector2<double> scale;
    sf::Sprite node;
    sf::Texture skin;
    int walkingCounter;
    sf::Clock walkingTimer;
    float lastTime;
    float walkDelay = 0.25;
    bool onGround;
    bool isJump;

  protected:
    void onFall();
    void onJump();
    
  public:
    GameObject();
    GameObject(GameObject&);
    GameObject(std::string, float, float, float sX = 1.0, float sY = 1.0);
    ~GameObject();
    void onUpdate();
    void jump();
    void moveLeft();
    void moveRight();
    void setColor(const sf::Color&);
    sf::Sprite* getNode();
    operator sf::Sprite();
  };
}

#endif /* gameObject_hpp */
