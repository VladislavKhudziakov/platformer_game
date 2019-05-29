
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

    
    checkHazards(map);
    detectPlayer();
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


  void Brain::detectPlayer()
  {
    if (GameData::playerPtr) {
      int tileSize = settings::sprite_resolution;
      
      int fovY = 2;
      int fovX = 4;
      int xMin;
      int xMax;
      int yMin;
      int yMax;
      
      const sf::FloatRect& playerHitbox = GameData::playerPtr->getHitbox();
      
      int playerMinX = playerHitbox.left / tileSize;
      int playerMaxX = (playerHitbox.left +  playerHitbox.width) / tileSize;
      int playerMinY = playerHitbox.top / tileSize;
      int playerMaxY = (playerHitbox.top +  playerHitbox.height) / tileSize;
      
      const sf::FloatRect& ownerHitBox = owner->getHitbox();
      
      if (currDirection == settings::unitsDirections::left) {
        xMin = ownerHitBox.left / tileSize - fovX;
        xMax = xMin + fovX;
      } else if (currDirection == settings::unitsDirections::right) {
        xMin = (ownerHitBox.left + ownerHitBox.width) / tileSize;
        xMax = xMin + fovX;
      }
      
      yMin = ownerHitBox.top / tileSize - fovY;
      yMax = (ownerHitBox.top + ownerHitBox.height) / tileSize + fovY;
      
      for (int y = yMin; y < yMax; y++) {
        for (int x = xMin; x < xMax; x++) {
          try {
            if ((x == playerMinX || x == playerMaxX) &&
                (y == playerMinY || y == playerMaxY)) {
              std::cout << owner->getName() + "'s dick is up\n";
              currMindState = settings::unitsMindStates::attack;
              return;
            }
          } catch (std::out_of_range err) {
            std::cerr << err.what() << std::endl;
          }
        }
      }
      currMindState = settings::unitsMindStates::patrol;
    }
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
