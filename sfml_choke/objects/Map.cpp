//
//  Map.cpp
//  platformer_game
//
//  Created by Vladislav Khudiakov on 5/18/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#include "Map.hpp"
#include <iostream>

namespace GO {
  
  Map::Map(int w, int h)
  {
    width = w;
    height = h;
    
    for (int i = 0; i < h; i++) {
      std:: string line;
      for (int j = 0; j < w; j++) {
        line += " ";
      }
      line += "\n";
      
      content += line;
    }
    
    std::cout << content;
  }
  
  Map::~Map() { };
}
