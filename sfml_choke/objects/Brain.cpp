
#include "Brain.hpp"

namespace GO {
  
  Brain::Brain(GameUnit* owner,
   settings::unitsDirections direction,
   settings::unitsMindStates mindState)
  {
    currDirection = direction;
    currMindState = mindState;
    this->owner = owner;
  }
  
  void Brain::think(const std::vector<std::string>& map)
  {
    if (currMindState == settings::unitsMindStates::patrol) {
      if (owner->onGround && currDirection == settings::unitsDirections::left) {
        owner->moveLeft();
      } else if (owner->onGround && currDirection == settings::unitsDirections::right) {
        owner->moveRight();
      }
    }

    if (currMindState == settings::unitsMindStates::attack) {
      attack(map);
    }
    
    checkHazards(map);
    detectPlayer(map);
  }
  
  
  void Brain::attack(const std::vector<std::string>& map)
  {
    if (currMindState == settings::unitsMindStates::attack) {
      int tileSize = settings::sprite_resolution;
      
      int ownerX = owner->hitBox.left / tileSize;
      
      if (currDirection == settings::unitsDirections::right) {
        ownerX = (owner->hitBox.left + owner->hitBox.width) / tileSize;
      }
      
      int ownerY = owner->hitBox.top / tileSize;
      
      const sf::FloatRect& playerHitbox = GameData::playerPtr->getHitbox();
      
      int playerX = playerHitbox.left / tileSize;
      int playerY = (playerHitbox.top +  playerHitbox.height) / tileSize;
      
      
      if (playerY < ownerY) {
        owner->jump();
      }
      else {
        if (ownerX > playerX) {
          currDirection = settings::unitsDirections::left;
          owner->moveLeft();
        } else if (ownerX < playerX) {
          currDirection = settings::unitsDirections::right;
          owner->moveRight();
        }
      }
    }
  }
  

  void Brain::checkHazards(const std::vector<std::string>& map)
  {
    if (currDirection == settings::unitsDirections::left) {
      checkHazardsByLeftSide(map);
    } else if (currDirection == settings::unitsDirections::right) {
      checkHazardsByRightSide(map);
    }
  }


  void Brain::checkHazardsByLeftSide(const std::vector<std::string>& map)
  {
    int tileSize = settings::sprite_resolution;
    int x = owner->hitBox.left / tileSize;
    int yMin = owner->hitBox.top / tileSize;
    int yMax = (owner->hitBox.top + owner->hitBox.height) / tileSize + 1;

    if (x >= 0) {
      for (int y = yMin; y < yMax; y++) {
        try {
          char mapBlockLabel = map.at(y).at(x);

          if (exist(settings::damageObjects, mapBlockLabel)) {
            currDirection = settings::unitsDirections::right;
          }

        } catch (std::out_of_range err) {
          std::cerr << err.what() << std::endl;
          return;
        }
      }
    }
  }


  void Brain::checkHazardsByRightSide(const std::vector<std::string>& map)
  {
    int tileSize = settings::sprite_resolution;

    int x = (owner->hitBox.left + owner->hitBox.width) / tileSize;
    int yMin = owner->hitBox.top / tileSize;
    int yMax = (owner->hitBox.top + owner->hitBox.height) / tileSize + 1;

    if (x < map.at(0).size()) {

      for (int y = yMin; y < yMax; y++) {
        try {
          char mapBlockLabel = map.at(y).at(x);

          if (exist(settings::damageObjects, mapBlockLabel)) {
            currDirection = settings::unitsDirections::left;
          }

        } catch (std::out_of_range err) {
          std::cerr << err.what() << std::endl;
          return;
        }
      }
    }
  }


  void Brain::detectPlayer(const std::vector<std::string>& map)
  {
    if (GameData::playerPtr) {
      int tileSize = settings::sprite_resolution;
      
      const sf::FloatRect& playerHitbox = GameData::playerPtr->getHitbox();
      
      int playerMinX = playerHitbox.left / tileSize;
      int playerMaxX = (playerHitbox.left +  playerHitbox.width) / tileSize - 1;
      int playerMinY = playerHitbox.top / tileSize;
      int playerMaxY = (playerHitbox.top +  playerHitbox.height) / tileSize - 1;
      
      sf::Vector2i fovYField = checkForWallsY(map);
      sf::Vector2i fovXField = checkForWallsX(map);
      
      for (int y = fovYField.x; y < fovYField.y; y++) {
        for (int x = fovXField.x; x < fovXField.y; x++) {
          try {
            if ((x == playerMinX || x == playerMaxX) &&
                (y == playerMinY || y == playerMaxY)) {
              currMindState = settings::unitsMindStates::attack;
              return;
            }
          } catch (std::out_of_range err) {
            std::cerr << owner->name + " player detection final loop is out of parameters\n";
          }
        }
      }
      currMindState = settings::unitsMindStates::patrol;
    }
  }
  
  
  sf::Vector2i Brain::checkForWallsY(const std::vector<std::string>& map)
  {
    int fovY = 2;
    
    int tileSize = settings::sprite_resolution;
    
    int ownerX = owner->getHitbox().left / tileSize + 1;
    int ownerY = owner->getHitbox().top / tileSize;
    
    if (currDirection == settings::unitsDirections::right) {
      ownerX = ownerX + owner->getHitbox().width / tileSize - 1;
    }
    
    int minFovY = ownerY - fovY;
    int maxFovY = ownerY + fovY;
    
    
    for (int y = minFovY; y < ownerY; y++) {
      try {
        if (exist(settings::walls, map.at(y).at(ownerX))) {
          minFovY = y;
        }
      } catch (std::out_of_range err) {
        std::cerr << owner->name + " player detection Y1 loop is out of parameters\n";
      }
    }
    
    int ownerBottomY = ownerY + owner->getHitbox().width / tileSize;
    
    for (int y = ownerBottomY + fovY; y > ownerBottomY; y--) {
      try {
        if (exist(settings::walls, map.at(y).at(ownerX))) {
          maxFovY = y;
        }
      } catch (std::out_of_range err) {
        std::cerr << owner->name + " player detection Y2 loop is out of parameters\n";
      }
    }
    
    return sf::Vector2i(minFovY, maxFovY);
  }
  
  
  sf::Vector2i Brain::checkForWallsX(const std::vector<std::string>& map)
  {
    int fovX = 4;
    
    int tileSize = settings::sprite_resolution;
    
    int ownerX = owner->getHitbox().left / tileSize;
    int ownerY = owner->getHitbox().top / tileSize;
    
    if (currDirection == settings::unitsDirections::right) {
      ownerX =  ownerX + owner->getHitbox().width / tileSize;
    };
    
    int minFovX;
    int maxFovX;
    
    if (currDirection == settings::unitsDirections::left) {
      minFovX = ownerX - fovX < 0 ? 0 : ownerX - fovX;
      maxFovX = ownerX;
      
      for (int x = minFovX; x < ownerX; x++) {
        try {
          if (exist(settings::walls, map.at(ownerY).at(x))) {
            minFovX = x;
          }
        } catch (std::out_of_range err) {
          std::cerr << owner->name + " player detection left loop is out of parameters\n";
        }
      }
    } else if (currDirection == settings::unitsDirections::right) {
      minFovX = ownerX;
      
      int mapSize;
      
      try {
        mapSize = map.at(ownerY).size();
      } catch (std::out_of_range err) {
        mapSize = map.at(0).size();
      }
      
      maxFovX = ownerX + fovX >= mapSize ? mapSize - 1 : ownerX + fovX;
      
      for (int x = maxFovX; x > ownerX; x--) {
        try {
          if (exist(settings::walls, map.at(ownerY).at(x))) {
            maxFovX = x;
          }
        } catch (std::out_of_range err) {
          std::cerr << owner->name + " player detection right loop is out of parameters\n";
        }
      }
    }
    
    return sf::Vector2i(minFovX , maxFovX);
  }


  void Brain::handleCollisionX(const CollisionObject& colObj)
  {
    if (exist(settings::walls, colObj.getLabel())) {
      
      if (currDirection == settings::unitsDirections::left) {
        currDirection = settings::unitsDirections::right;
      } else if (currDirection == settings::unitsDirections::right) {
        currDirection = settings::unitsDirections::left;
      }
    }
  }
}
