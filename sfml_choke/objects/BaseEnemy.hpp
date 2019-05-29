
#ifndef baseEnemy_hpp
#define baseEnemy_hpp

#include "Brain.hpp"
#include "gameUnit.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

typedef settings::unitsDirections unitsDir;

namespace GO {
  
  class BaseEnemy : public GameUnit
  {
  private:
    Brain* brain;
    
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
    
    virtual ~BaseEnemy();
    
    void onUpdate(double, const std::vector<std::string>&) override;
    };
}

#endif /* baseEnemy_hpp */
