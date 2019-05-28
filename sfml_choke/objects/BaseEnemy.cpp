#include "BaseEnemy.hpp"


namespace GO {
  
  BaseEnemy::BaseEnemy(const sf::Texture& texture, const std::string& name,
   float x, float y, unitsDir direction) : GameUnit(texture, name, x, y)
  {
    currDirection = direction;
    dx = 0.1;
  }
  
  
  BaseEnemy::BaseEnemy(const std::string& texName, const std::string& name,
   float x, float y, unitsDir direction) : GameUnit(texName, name, x, y)
  {
    currDirection = direction;
    dx = 0.1;
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
  
  
  void BaseEnemy::onUpdate(double delta, const std::vector<std::string>& map)
  {
    if (isJump) {
      sf::Vector2f point = getPosition();
      double jumpHeight = settings::jumpSize * settings::sprite_resolution;
      
      if (!(point.y + hitBox.height >= jumpStartY - jumpHeight)) {
        isJump = false;
      }
    }
    
    if (onGround && currDirection == unitsDir::left) {
      moveLeft();
    } else if (onGround && currDirection == unitsDir::right) {
      moveRight();
    }
    
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
