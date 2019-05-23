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
    player = new GO::GameUnit("player.png", 100, 100);
    player->moveTo(100, 100);
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
    double now = timer.getElapsedTime().asMicroseconds();
    double deltaTime = now - prevFrameTime;
    prevFrameTime = now;
    
    gameWindow->clear();
    renderMap();
    player->stop();
    inputKeysHandler();
    player->onUpdate(deltaTime, map.get());
//    checkCollisions();
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
      
      const std::vector<std::string>& mapContent = map.get();
      
      for (int i = 0; i < mapContent.size(); i++) {
        for (int j = 0; j < mapContent[i].length(); j++) {
          if (mapContent.at(i).at(j) == 'b') {
            GO::MapSprite* mapBlock = new GO::MapSprite("wall.png");

            int spritePositionX = j * settings::sprite_resolution;
            int spritePositionY = i * settings::sprite_resolution;

            mapBlock->setPosition(spritePositionX, spritePositionY);

            mapObjects.push_back(mapBlock);
          }
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
    const sf::FloatRect& playerHitbox = player->getHitbox();
    using settings::sprite_resolution;
    
    int playerTopMin = playerHitbox.top / sprite_resolution;
    int playerTopMax = (playerHitbox.top + sprite_resolution * 2) / sprite_resolution;
    int playerLeftMin = playerHitbox.left / sprite_resolution;
    int playerLeftMax = (playerHitbox.left + sprite_resolution) / sprite_resolution;
    std::vector<std::string> mapContent = map.get();
    
    
    for (int i = playerTopMin; i < playerTopMax; i++) {
      for (int j = playerLeftMin; j < playerLeftMax; j++) {
        try {
          if (mapContent.at(i).at(j) == 'b') {
            std::cout<< "i: " << i << " j: " << j << std::endl;
//
//            double deltaX = player->getHitbox().left;
//            double deltaY = player->getHitbox().top;
//
//            double playerDirectionX = player->getDirectionX();
//            double playerDirectionY = player->getDirectionY();
//            if (playerDirectionX > 0) {
//              deltaX = j * 32 - 32;
//            } else if (playerDirectionX < 0) {
//              deltaX = j * 32 + 32;
//            }
//            if (playerDirectionY > 0) {
//              deltaY = i * 32 - 32 * 2;
//            } else if (playerDirectionY < 0) {
//              deltaY = i * 32 + 32;
//
//            }
//
//            player -> moveTo(deltaX, deltaY);
            

          }
        } catch (std::out_of_range) {
          std::cout <<  "out of parameters i:" << i << "j: " << j << std::endl;
        }
        
      }
    }
    
//    for (int i = playerTopMin; i < playerTopMax; i++) {
//      for (int j = playerLeftMin; j < playerLeftMax; j++) {
//
//        try {
//          if (mapContent.at(i).at(j) == 'b') {
//            std::cout << "i " << i << " j " << j << std::endl;
//            double playerDirection = player->getDirectionY();
//
//            if (playerDirection > 0) {
//              double posY = i * 32 - 32 * 2;
//              player -> moveTo(playerHitbox.left, posY);
//              player -> getOnTheGround();
//            } else if (playerDirection < 0) {
//              double posY = i * 32 + 32;
//              player -> moveTo(playerHitbox.left, posY);
//              player -> fall();
//            }
//          }
//        } catch (std::out_of_range) {
//          std::cout <<  "out of parameters i:" << i << " j: " << j << std::endl;
//        }
//      }
//    }
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
    timer.restart();
    prevFrameTime = timer.getElapsedTime().asMicroseconds();
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
      
      onUpdate();
      
    }
  }
  
  
  void Game::stop() { }
}
