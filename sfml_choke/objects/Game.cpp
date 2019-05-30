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
    player = new GO::GameUnit("player.png", "player", 100, 100);
    
    for (int i = 132, j = 1; i < 132 + 32 * 5; i += 32, j++) {
      auto unit = new GO::BaseEnemy("player.png", "enemy" + std::to_string(j), i, 100, j % 2 == 0 ? unitsDir::left : unitsDir::right, settings::unitsMindStates::patrol);
      units.push_back(unit);
    }
  }
  
  
  Game::~Game()
  {
    delete gameWindow;
    delete player;
    
    for (auto tile : tiles) {
      delete tile;
    }
    
    for (auto unit : units) {
      delete unit;
    }
  }
  
  
  void Game::inputKeysHandler()
  {
    if (sf::Keyboard::isKeyPressed(settings::moveLeftKey)) {
      if (player) player->moveLeft();
    }
    
    if (sf::Keyboard::isKeyPressed(settings::moveRightKey)) {
      if (player) player->moveRight();
    }
    
    if (sf::Keyboard::isKeyPressed(settings::jumpKey)) {
      if (player) player->jump();
    }
  }
  
  
  void Game::onUpdate()
  {
    double now = timer.getElapsedTime().asMicroseconds();
    double deltaTime = now - prevFrameTime;
    auto currMap = map.get();
    
    prevFrameTime = now;
    
    gameWindow->clear();
    renderMap();
    
    renderUnits(deltaTime, currMap);
    
    inputKeysHandler();
    
    renderPlayer(deltaTime, currMap);
    
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
          if (settings::tileMap.count(mapContent[i][j]) > 0) {
            GO::MapSprite* mapBlock = new GO::MapSprite("tileSet.png");
            
            int spritePositionX = j * settings::sprite_resolution;
            int spritePositionY = i * settings::sprite_resolution;
            
            mapBlock->setPosition(spritePositionX, spritePositionY);
            auto texPos = settings::tileMap.at(mapContent[i][j]);
            
            int rectLeft = texPos.x * settings::sprite_resolution;
            int rectTop = texPos.y * settings::sprite_resolution;
            int width = settings::sprite_resolution;
            int height = settings::sprite_resolution;
            
            mapBlock->setTextureRect(sf::IntRect(rectLeft, rectTop, width, height));
            mapBlock->calculateSpriteScale();
            
            tiles.push_back(mapBlock);
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
    for (GO::MapSprite* tile : tiles) {
      gameWindow->draw(*tile);
    }
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
  
   void Game::renderUnits(double delta, const std::vector<std::string>& currMap)
  {
    for (GO::GameUnit* unit : units) {
      renderUnit(unit, delta, currMap);
    }
  }

  
  void Game::start()
  {
    loadMap("Map.txt");
    map.calculateSize();
    buildMap();
    timer.restart();
    
    GameData::playerPtr = player;
    
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
  
  
  void Game::renderPlayer(double delta, const std::vector<std::string>& map)
  {
    if (player && player->getHp() <= 0) {
      delete player;
      player = nullptr;
      GameData::playerPtr = nullptr;
    }
    
    if (player) {
      player->onUpdate(delta, map);
      gameWindow->draw(*player);
    }
  }
  
  
  void Game::renderUnit(GO::GameUnit* unit, double delta, const std::vector<std::string>& map)
  {
    bool isDeleted = false;
    
    if (unit && unit->getHp() <= 0) {
      
      delete unit;
      auto unitIter = std::find(units.begin(), units.end(), unit);
      if (unitIter != units.end()) {
        units.erase(unitIter);
      }
      
      isDeleted = true;
    }
    
    if (!isDeleted) {
      unit->onUpdate(delta, map);
      gameWindow->draw(*unit);
    }
  }
  
  
  void Game::stop() { }
}
