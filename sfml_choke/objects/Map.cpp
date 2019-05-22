//
//  Map.cpp
//  platformer_game
//
//  Created by Vladislav Khudiakov on 5/18/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#include "Map.hpp"
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
  
  
  void Map::calculateSize()
  {
    int lastMaxSize = 0;
    int maxLineSize = 0;
    int linesCount = 0;
    
    for (char strChar : content) {
      if (strChar != '\n') {
        maxLineSize++;
      } else {
        lastMaxSize = maxLineSize > lastMaxSize ? maxLineSize : lastMaxSize;
        linesCount++;
        maxLineSize = 0;
      }
    }
    
//    std::cout << lastMaxSize << std::endl;
    width = lastMaxSize;
    height = linesCount;
  }
  
  
  sf::Vector2f Map::getSize()
  {
    return sf::Vector2f(width, height);
  }
  
  
  const std::string& Map::getFileContent()
  {
    return content;
  }
  
  
  Map::~Map() { };
}
