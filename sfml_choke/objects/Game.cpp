//
//  Game.cpp
//  sfml_choke
//
//  Created by Vladislav Khudiakov on 5/16/19.
//  Copyright © 2019 Vladislav Khudiakov. All rights reserved.
//

#include "Game.hpp"
#include <iostream>
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
    
    player->onUpdate();

    gameWindow->draw(*player);
    
    gameWindow->display();
  }
  
  
  void Game::start()
  {
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
