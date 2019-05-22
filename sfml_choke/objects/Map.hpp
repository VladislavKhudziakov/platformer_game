//
//  Map.hpp
//  platformer_game
//
//  Created by Vladislav Khudiakov on 5/18/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#ifndef Map_hpp
#define Map_hpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "gameUnit.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "../global.h"

namespace GO {
  class Map
  {
  private:
    std::string content;
    std::string fileName;
    int width;
    int height;
    
  public:
    Map();
    Map(const std::string&);
    void loadFromFile(const std::string&);
    void calculateSize();
    const std::string& getFileContent();
    sf::Vector2f getSize();
    ~Map();
  };
}

#endif /* Map_hpp */
