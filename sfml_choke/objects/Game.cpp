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
    player = new GO::GameUnit("player.png", 100, 100, 0.5, 0.5);
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
    
    checkCollisions();
    player->onUpdate();
    
    gameWindow->draw(*player);
    
    gameWindow->display();
  }
  
  
  void Game::loadMap(const std::string& fileName)
  {
    map.loadFromFile(fileName);
  }
  
  
  double Game::calculateMapSpriteSizeAspect(const GO::mapBlockData& blockData)
  {
    if (blockData.width >= blockData.height) {
      return  blockData.height / blockData.width;
    } else {
      return blockData.width / blockData.height;
    }
  }
  
  
  void Game::buildMap()
  {
    GO::mapBlockData blockData = getBlocksData();
    
    double sizeAspect = calculateMapSpriteSizeAspect(blockData);
    
    std::string mapContent = map.getFileContent();
    
    try {
      assertMapBuilding();
      
      int currLine = 0;
      int currColumn = 0;
      
      for (char strChar : mapContent) {
        if (strChar != '\n') {
          currColumn++;
          if (strChar == 'b') {
            GO::MapSprite* mapBlock = new GO::MapSprite("wall.png");
            
            mapBlock->scale(mapBlock->calculateSpriteScale(blockData, sizeAspect));

            sf::Vector2f currPos(
              currColumn * blockData.width, currLine * blockData.height);
            
            mapBlock->setPosition(currPos);
            
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
    for (GO::MapSprite* currBlock : mapObjects) {
      gameWindow->draw(*currBlock);
    }
  }
  
  
  void Game::checkCollisions()
  {
//    sf::Vector2<unsigned int> size = player->getTexture()->getSize();
//    sf::Vector2f scale = player->getScale();
//    double width = scale.x * size.x;
//    double height = scale.y * size.y;
//    sf::Vector2f position = player->getPosition();
//
//    double playerLeft = position.x - width / 2;
//    double playerRight = position.x + width / 2;
//    double playerTop = position.y + height / 2;
//    double playerBottom = position.y - height / 2;
    
    for (GO::MapSprite* currBlock : mapObjects) {
      
//      sf::Vector2<unsigned int> size = currBlock->getTexture()->getSize();
//      sf::Vector2f scale = currBlock->getScale();
//      double width = scale.x * size.x;
//      double height = scale.y * size.y;
//      sf::Vector2f position = currBlock->getPosition();
//
//      double tileLeft = position.x - width / 2;
//      double tileRight = position.x + width / 2;
//      double tileTop = position.y + height / 2;
//      double tileBottom = position.y - height / 2;
      
//      if (playerTop > tileBottom || playerBottom < tileTop || playerRight < tileLeft || playerLeft > tileRight)
//      {
//
//      } else {
//        std::cout << "player: " << playerTop << std::endl;
//        std::cout << "tile: " << tileTop << std::endl;
//      }

    }
  }
  
  
  GO::mapBlockData Game::getBlocksData()
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

        if (event.type == sf::Event::KeyPressed &&
            event.key.code == sf::Keyboard::Escape) {
          gameWindow->close();
        }
      }

      inputKeysHandler();
      onUpdate();
    }
  }
  
  
  void Game::stop() { }
}
