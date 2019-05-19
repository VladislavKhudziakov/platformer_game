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
  
  
  double Game::calculateMapSpriteCoeff(const Game::mapBlockData& blockData)
  {
    if (blockData.width >= blockData.height) {
      return  blockData.height / blockData.width;
    } else {
      return blockData.width / blockData.height;
    }
  }
  
  
  sf::Vector2f Game::calculateSpriteScale(
    const sf::Sprite* mapSprite, const Game::mapBlockData& blockData, double sizeCoeff)
  {
    if (blockData.width >= blockData.height) {
      
      sf::Vector2f spriteSize(
        blockData.width * sizeCoeff, blockData.height);
      
      auto textureSize = mapSprite->getTexture()->getSize();
      
      return sf::Vector2f(
        spriteSize.x / textureSize.x, spriteSize.y / textureSize.y);
      
    } else {
      sf::Vector2f spriteSize(
        blockData.width, blockData.height * sizeCoeff);
      
      auto textureSize = mapSprite->getTexture()->getSize();
      
      return sf::Vector2f(
       spriteSize.x / textureSize.x, spriteSize.y / textureSize.y);
      
    }
  }
  
  
  void Game::buildMap()
  {
    Game::mapBlockData blockData = calculateBlockSize();
    
    double sizeCoeff = calculateMapSpriteCoeff(blockData);
    
    auto mapContent = map.getFileContent();
    
    try {
      assertMapBuilding();
      
      int currLine = 0;
      int currColumn = 0;
      
      for (char strChar : mapContent) {
        if (strChar != '\n') {
          currColumn++;
          
          if (strChar == 'b') {
            auto texture = new sf::Texture();
            
            texture->loadFromFile(resourcePath() + "wall.png");
            auto mapBlock = new sf::Sprite(*texture);
            
            mapBlock->scale(calculateSpriteScale(mapBlock, blockData, sizeCoeff));
            
            sf::Vector2f currPos(
              currColumn * blockData.width, currLine * blockData.height);
            
            mapBlock->setPosition(currPos.x, currPos.y);
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
    for (sf::Drawable* currBlock : mapObjects) {
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
