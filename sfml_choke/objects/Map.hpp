//
//  Map.hpp
//  platformer_game
//
//  Created by Vladislav Khudiakov on 5/18/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#ifndef Map_hpp
#define Map_hpp

#include <string>

namespace GO {
  class Map
  {
  private:
    std::string content;
    int width;
    int height;
    
  public:
    Map(int, int);
    ~Map();
  };
}

#endif /* Map_hpp */
