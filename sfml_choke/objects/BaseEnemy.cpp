#include "BaseEnemy.hpp"


namespace GO {
//  class BaseEnemy : public GameUnit
//  {
//  protected:
//    bool isCollised;
//
//  public:
//    BaseEnemy(const sf::Texture& tex, const std::string& name, float x, float y);
//    BaseEnemy(const std::string& texName, const std::string& name, float x, float y);
//  };
  
  BaseEnemy::BaseEnemy(const sf::Texture& texture, const std::string& name, float x, float y)
    : GameUnit(texture, name, x, y)
  {
    dx = 0.1;
  }
  
  BaseEnemy::BaseEnemy(const std::string& texName, const std::string& name, float x, float y)
  : GameUnit(texName, name, x, y)
  {
    dx = 0.1;
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
    
    hitBox.top += dy * delta / 200;
    detectCollisionY(map);
    
    hitBox.left += dx * delta / 200;
    detectCollisionX(map);
    
    setPosition(hitBox.left, hitBox.top);
    
    
//    if () {
//      std::cout << name + " collised X " << o.getPosition().x << "\n";
//    }
    
//    if (o.getLabel()) {
//      std::cout << name + " collised Y " << colYObj << "\n";
//    }
    
    dx = 0;
    
    if (!isJump) {
      dy = settings::gravityForce;
    }
  }
}
