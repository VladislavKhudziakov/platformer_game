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
    gameWindow = new sf::RenderWindow();
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
    
//    player->onUpdate();

    checkCollisions();
    
    gameWindow->draw(*player);
    
    gameWindow->display();
  }
  
  
  void Game::loadMap(const std::string& fileName)
  {
    map.loadFromFile(fileName);
  }
  
  
  void Game::buildMap()
  {
    try {
      assertMapBuilding();
      
      sf::Vector2f mapSize = map.getSize();
      
      settings::windowWidth = mapSize.x * settings::sprite_resolution;
      settings::windowHeight = mapSize.y * settings::sprite_resolution;
      
      gameWindow->create(sf::VideoMode(
       settings::windowWidth, settings::windowHeight), "title");
      
      std::string mapContent = map.getFileContent();
      
      int currLine = 0;
      int currColumn = 0;
      
      for (char strChar : mapContent) {
        if (strChar != '\n') {
          currColumn++;
          if (strChar == 'b') {
            GO::MapSprite* mapBlock = new GO::MapSprite("wall.png");
            
            int spritePositionX = currColumn * settings::sprite_resolution;
            int spritePositionY = currLine * settings::sprite_resolution;
            
            mapBlock->setPosition(spritePositionX, spritePositionY);
            
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
  }
  
  
  void Game::assertMapBuilding()
  {
    sf::Vector2f mapSize = map.getSize();
    if (mapSize.x > 0 && mapSize.y > 0) {
      return;
    } else {
      throw std::logic_error("invalid map size.\n");
    }
  }

  
  void Game::start()
  {
    loadMap("Map.txt");
    map.calculateSize();
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
