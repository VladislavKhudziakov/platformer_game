//
//  Map.cpp
//  platformer_game
//
//  Created by Vladislav Khudiakov on 5/18/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#include "Map.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include "ResourcePath.hpp"

namespace GO {
  
  Map::Map() { };
  

  Map::Map(const std::string& fileName)
  {
    loadFromFile(fileName);
  }
  
  
  void Map::loadFromFile(const std::string& fileName)
  {
    this->fileName = fileName;
    std::ifstream fin;
    std::stringstream strStream;
    fin.open(resourcePath() + fileName);
    
    if (!fin.is_open()) {
      std::cout << "error in map loading\n";
    } else {
      strStream << fin.rdbuf();
      content = strStream.str();
      fin.close();
      std::cout << "map loaded successful\n";
    }
  }
  
  
  const std::string& Map::getFileContent()
  {
    return content;
  }
  
  
  Map::~Map() { };
}
