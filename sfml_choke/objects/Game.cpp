//
//  Game.cpp
//  sfml_choke
//
//  Created by Vladislav Khudiakov on 5/16/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#include "Game.hpp"

namespace GO {
  
  Game::Game()
  {
    gameWindow = new sf::RenderWindow(
    sf::VideoMode(settings::windowWidth, settings::windowHeiht), "Game");
    player = new GO::GameObject("player.png", 100, 100, 0.5, 0.5);
  }
  
  
  Game::~Game()
  {
    delete gameWindow;
    delete player;
    
    for (auto object : mapObjects) {
      delete object;
    }
    
  }
  
  
  void Game::inputKeysHandler()
  {
    if (sf::Keyboard::isKeyPressed(settings::moveLeftKey)) {
      player->moveLeft();
    }
    
    if (sf::Keyboard::isKeyPressed(settings::moveRightKey)) {
      player->moveRight();
    }
    
    if (sf::Keyboard::isKeyPressed(settings::jumpKey)) {
      player->jump();
    }
  }
  
  
  void Game::onUpdate()
  {
    gameWindow->clear();
    
    renderMap();
    
    player->onUpdate();
    
    gameWindow->draw(*player);
    
    gameWindow->display();
  }
  
  
  void Game::loadMap(const std::string& fileName)
  {
    map.loadFromFile(fileName);
  }
  
  
  void Game::buildMap()
  {
    Game::mapBlockData blockData = calculateBlockSize();
    
    auto mapContent = map.getFileContent();
    
    try {
      assertMapBuilding();
      
      int currLine = 0;
      int currColumn = 0;
      
      for (char strChar : mapContent) {
        if (strChar != '\n') {
          currColumn++;
          
          if (strChar == 'b') {
            auto mapBlock = new sf::RectangleShape();
            mapBlock->setSize(sf::Vector2f(blockData.width, blockData.height));
            
            sf::Vector2f currPos;
            
            currPos.x = currColumn * blockData.width;
            currPos.y = currLine * blockData.height;
            
            
            mapBlock->setPosition(currPos);
            mapBlock->setFillColor(sf::Color::White);
            
            mapObjects.push_back(mapBlock);
          }
          
        } else {
          currLine++;
          currColumn = 0;
        }
      }
      
    } catch (std::logic_error err) {
      std::cout << err.what();
      std::cout << "cannot build map from empty file or empty map";
    }
  }
  
  
  void Game::renderMap()
  {
    for (sf::RectangleShape* currBlock : mapObjects) {
      gameWindow->draw(*currBlock);
    }
  }
  
  
  Game::mapBlockData Game::calculateBlockSize()
  {
   mapBlockData blocksData;
    
    auto mapContent = map.getFileContent();
    
    int lastMaxSize = 0;
    int maxLineSize = 0;
    int linesCount = 0;
    
    try {
      assertMapBuilding();
      
      for (char strChar : mapContent) {
        if (strChar != '\n') {
          maxLineSize++;
        } else {
          lastMaxSize = maxLineSize > lastMaxSize ? maxLineSize : lastMaxSize;
          linesCount++;
          maxLineSize = 0;
        }
      }
      
      blocksData.width = settings::windowWidth / lastMaxSize;
      blocksData.height = settings::windowHeiht / linesCount;
      blocksData.columnsCount = lastMaxSize;
      blocksData.linesCount = linesCount;
      
    } catch (std::logic_error err) {
      std::cout << err.what();
      std::cout << "cannot build map from empty file or empty map";
    }
    
    return blocksData;
  }
  
  
  void Game::assertMapBuilding()
  {
    auto mapContent = map.getFileContent();
    if (mapContent.size() > 0) {
      return;
    } else {
      throw std::logic_error("invalid map size.\n");
    }
  }

  
  
  void Game::start()
  {
    loadMap("Map.txt");
    buildMap();
    
    while (gameWindow->isOpen())
    {
      sf::Event event;

      while (gameWindow->pollEvent(event))
      {
        if (event.type == sf::Event::Closed) {
          gameWindow->close();
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
          gameWindow->close();
        }
      }

      inputKeysHandler();
      onUpdate();
    }
  }
  
  
  void Game::stop() { }
}
