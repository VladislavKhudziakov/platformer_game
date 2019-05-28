
#ifndef baseEnemy_hpp
#define baseEnemy_hpp

#include "gameUnit.hpp"
typedef settings::unitsDirections unitsDir;

namespace GO {
  class BaseEnemy : public GameUnit
  {
  protected:
    unitsDir currDirection = unitsDir::none;
    void handleCollisionX(const CollisionObject&) override;
    void handleCollisionY(const CollisionObject&) override;
    
  public:
    BaseEnemy(const sf::Texture&, const std::string&,
              float x = 0, float y = 0,
              unitsDir startDirection = unitsDir::none);
    
    BaseEnemy(const std::string&, const std::string&,
              float x = 0, float y = 0,
              unitsDir startDirection = unitsDir::none);
    
    void onUpdate(double, const std::vector<std::string>&) override;
  };
}

#endif /* baseEnemy_hpp */
