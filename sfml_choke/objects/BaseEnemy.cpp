#include "BaseEnemy.hpp"


namespace GO {
  
  BaseEnemy::BaseEnemy(const sf::Texture& texture, const std::string& name,
   float x, float y, unitsDir direction) : GameUnit(texture, name, x, y)
  {
    brain = new GO::Brain(this);
    currDirection = direction;
    dx = 0.1;
  }
  
  
  BaseEnemy::BaseEnemy(const std::string& texName, const std::string& name,
   float x, float y, unitsDir direction) : GameUnit(texName, name, x, y)
  {
    brain = new GO::Brain(this);
    currDirection = direction;
    dx = 0.1;
  }
  
  
  BaseEnemy::~BaseEnemy()
  {
    delete brain;
  }
  
  
  void BaseEnemy::handleCollisionX(const CollisionObject& colObj)
  {
    GameUnit::handleCollisionX(colObj);
    if (exist(settings::walls, colObj.getLabel())) {
      
      if (currDirection == unitsDir::left) {
        currDirection = unitsDir::right;
      } else if (currDirection == unitsDir::right) {
        currDirection = unitsDir::left;
      }
    }
  }
  
  
  void BaseEnemy::handleCollisionY(const CollisionObject& colObj)
  {
    GameUnit::handleCollisionY(colObj);
  }
  
  
  void BaseEnemy::checkForDamageObjects(const std::vector<std::string>& map)
  {
    if (currDirection == unitsDir::left) {
      checkLeft(map);
    } else if (currDirection == unitsDir::right) {
      checkRight(map);
    }
  }
  
  
  void BaseEnemy::checkLeft(const std::vector<std::string>& map)
  {
    int tileSize = settings::sprite_resolution;
    int x = hitBox.left / tileSize;
    int yMin = hitBox.top / tileSize;
    int yMax = (hitBox.top + hitBox.height) / tileSize + 1;
    
    if (x >= 0) {
      for (int y = yMin; y < yMax; y++) {
        try {
         char mapBlockLabel = map.at(y).at(x);
          
          if (exist(settings::damageObjects, mapBlockLabel)) {
            currDirection = unitsDir::right;
          }
          
        } catch (std::out_of_range err) {
          std::cerr << err.what() << std::endl;
          std::cerr <<name + ": out of range error: y position is out of range\n";
          return;
        }
      }
    }
  }
  
  
  void BaseEnemy::checkRight(const std::vector<std::string>& map)
  {
    int tileSize = settings::sprite_resolution;
    int x = (hitBox.left + hitBox.width) / tileSize;
    int yMin = hitBox.top / tileSize;
    int yMax = (hitBox.top + hitBox.height) / tileSize + 1;

    if (x < map.at(0).size()) {
      
      for (int y = yMin; y < yMax; y++) {
        try {
          char mapBlockLabel = map.at(y).at(x);
          
          if (exist(settings::damageObjects, mapBlockLabel)) {
            currDirection = unitsDir::left;
          }
          
        } catch (std::out_of_range err) {
          std::cerr << err.what() << std::endl;
          std::cerr <<name + ": out of range error: y position is out of range\n";
          return;
        }
      }
    }
  }
  
  
  void BaseEnemy::checkForPlayer(const sf::FloatRect& playerHitbox)
  {
    int tileSize = settings::sprite_resolution;
    
    int fovY = 2;
    int fovX = 4;
    int xMin;
    int xMax;
    int yMin;
    int yMax;
    
    int playerMinX = playerHitbox.left / tileSize;
    int playerMaxX = (playerHitbox.left +  playerHitbox.width) / tileSize;
    int playerMinY = playerHitbox.top / tileSize;
    int playerMaxY = (playerHitbox.top +  playerHitbox.height) / tileSize;
    
    if (currDirection == unitsDir::left) {
      xMin = hitBox.left / tileSize;
      xMax = xMin - fovX;
    } else if (currDirection == unitsDir::right) {
      xMin = (hitBox.left + hitBox.width) / tileSize;
      xMax = xMin + fovX;
    }
    
    yMin = hitBox.top / tileSize - fovY;
    yMax = (hitBox.top + hitBox.height) / tileSize + fovY;
    
    for (int y = yMin; y < yMax; y++) {
      for (int x = xMin; x < xMax; x++) {
        try {
          if ((x == playerMinX || x == playerMaxX) && (y == playerMinY || y == playerMaxY)) {
            std::cout << name + "'s dick is up\n";
          }
        } catch (std::out_of_range) {
        }
      }
    }
  }
  
  
  void BaseEnemy::onUpdate(double delta, const std::vector<std::string>& map)
  {
    if (isJump) {
      sf::Vector2f point = getPosition();
      double jumpHeight = settings::jumpSize * settings::sprite_resolution;
      
      if (!(point.y + hitBox.height >= jumpStartY - jumpHeight)) {
        isJump = false;
      }
    }
    
//    brain->think(map);
    if (onGround && currDirection == unitsDir::left) {
      moveLeft();
    } else if (onGround && currDirection == unitsDir::right) {
      moveRight();
    }

    checkForDamageObjects(map);

    checkForPlayer(GameData::playerPtr->getHitbox());
    
    hitBox.top += dy * delta / 200;
    detectCollisionY(map);
    
    hitBox.left += dx * delta / 200;
    detectCollisionX(map);
    
    setPosition(hitBox.left, hitBox.top);
    
    dx = 0;
    
    if (!isJump) {
      dy = settings::gravityForce;
    }
  }
}
