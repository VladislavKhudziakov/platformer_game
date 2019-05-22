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
      std::string mapSting = strStream.str();
      fin.close();
      mapSting.pop_back();
      boost::split(content, mapSting, boost::is_any_of("\n"));
      std::cout << "map loaded successful\n";
    }
  }
  
  
  void Map::calculateSize()
  {
    int lastMaxSize = 0;
    int maxLineSize = 0;
    int linesCount = 0;
    
    auto it = std::max_element(content.begin(), content.end(),
     [](const std::string& s1, const std::string& s2) {
       return s1.length() < s2.length();
     });
    
    width = it->length();
    height = content.size();
  }
  
  
  sf::Vector2f Map::getSize()
  {
    return sf::Vector2f(width, height);
  }
  
  
  const std::vector<std::string>& Map::get()
  {
    return content;
  }
  
  
  Map::~Map() { };
}
