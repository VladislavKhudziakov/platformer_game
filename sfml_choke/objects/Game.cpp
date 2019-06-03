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
    for (int i = 132, j = 1; i < 132 + 32 * 5; i += 32, j++) {
      auto unit = new GO::BaseEnemy("player.png", "enemy" + std::to_string(j), i, 100, j % 2 == 0 ? unitsDir::left : unitsDir::right);
        GameData::activeUnits.push_back(unit);
    }
  }
  
  
  Game::~Game()
  {
    delete gameWindow;
  }
  
  
  void Game::inputKeysHandler()
  {
    if (sf::Keyboard::isKeyPressed(settings::moveLeftKey)) {
      if (GameData::player) GameData::player->moveLeft();
    }
    
    if (sf::Keyboard::isKeyPressed(settings::moveRightKey)) {
      if (GameData::player) GameData::player->moveRight();
    }
    
    if (sf::Keyboard::isKeyPressed(settings::jumpKey)) {
      if (GameData::player) GameData::player->jump();
    }
  }
  
  
  void Game::onUpdate()
  {
    double now = timer.getElapsedTime().asMicroseconds();
    double deltaTime = now - prevFrameTime;
    auto currMap = GameData::map->get();
    
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
    GameData::map->loadFromFile(fileName);
  }
  
  
  void Game::buildMap()
  {
    try {
      assertMapBuilding();
      
      sf::Vector2f mapSize = GameData::map->getSize();
      
      settings::windowWidth = mapSize.x * settings::sprite_resolution;
      settings::windowHeight = mapSize.y * settings::sprite_resolution;
      
      gameWindow->create(sf::VideoMode(
       settings::windowWidth, settings::windowHeight), "title");
      
      const std::vector<std::string>& mapContent = GameData::map->get();
      
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
            
            GameData::mapTiles.push_back(mapBlock);
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
    for (GO::MapSprite* tile : GameData::mapTiles) {
      gameWindow->draw(*tile);
    }
  }
  
  
  void Game::assertMapBuilding()
  {
    sf::Vector2f mapSize = GameData::map->getSize();
    if (mapSize.x > 0 && mapSize.y > 0) {
      return;
    } else {
      throw std::logic_error("invalid map size.\n");
    }
  }
  
   void Game::renderUnits(double delta, const std::vector<std::string>& currMap)
  {
    for (GO::GameUnit* unit : GameData::activeUnits) {
      renderUnit(unit, delta, currMap);
    }
  }

  
  void Game::start()
  {
    GameData::map = new GO::Map();
    loadMap("Map.txt");
    GameData::map->calculateSize();
    buildMap();
    timer.restart();
    GameData::player = new GO::GameUnit("player.png", "player", 100, 100);
    
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
    if (GameData::player && GameData::player->getHp() <= 0) {
      delete GameData::player;
      GameData::player = nullptr;
    }
    
    if (GameData::player) {
      GameData::player->onUpdate(delta);
      gameWindow->draw(*GameData::player);
    }
  }
  
  
  void Game::renderUnit(GO::GameUnit* unit, double delta, const std::vector<std::string>& map)
  {
    bool isDeleted = false;
    
    if (unit && unit->getHp() <= 0) {
      
      delete unit;
      auto unitIter = std::find(GameData::activeUnits.begin(), GameData::activeUnits.end(), unit);
      
      if (unitIter != GameData::activeUnits.end()) {
        GameData::activeUnits.erase(unitIter);
      }
      
      isDeleted = true;
    }
    
    if (!isDeleted) {
      unit->onUpdate(delta);
      gameWindow->draw(*unit);
    }
  }
  
  
  void Game::stop() { }
}
