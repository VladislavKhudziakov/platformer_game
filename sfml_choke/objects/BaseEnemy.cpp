#include "BaseEnemy.hpp"


namespace GO {
  
  BaseEnemy::BaseEnemy(const sf::Texture& texture, const std::string& name,
   float x, float y, unitsDir direction)
    : GameUnit(texture, name, x, y)
  {
    brain = new GO::Brain(this, direction);
    currDirection = direction;
    dx = 0.1;
  }
  
  
  BaseEnemy::BaseEnemy(const std::string& texName, const std::string& name,
   float x, float y, unitsDir direction)
    : GameUnit(texName, name, x, y)
  {
    brain = new GO::Brain(this, direction);
    currDirection = direction;
    dx = 0.1;
  }
  
  
  BaseEnemy::BaseEnemy(const BaseEnemy& other)
    : GameUnit(*other.getTexture(), other.name, other.hitBox.left, other.hitBox.top)
  {
    brain = new Brain(this);
  }
  
  
  BaseEnemy::BaseEnemy(): GameUnit()
  {
    brain = nullptr;
  }
  
  
  BaseEnemy::~BaseEnemy()
  {
    delete brain;
  }
  
  
  void BaseEnemy::handleCollisionX(const CollisionObject& colObj)
  {
    GameUnit::handleCollisionX(colObj);
    brain->handleCollisionX(colObj);
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
    
    brain->think(map);
    
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
