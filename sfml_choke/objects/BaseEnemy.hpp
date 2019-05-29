
#ifndef baseEnemy_hpp
#define baseEnemy_hpp

#include "Brain.hpp"
#include "gameUnit.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

typedef settings::unitsDirections unitsDir;
typedef settings::unitsMindStates mindStates;

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
    BaseEnemy();
    
    BaseEnemy(const sf::Texture&, const std::string&,
              float x = 0, float y = 0,
              unitsDir startDirection = unitsDir::none,
              mindStates mindState = mindStates::stand);
    
    BaseEnemy(const std::string&, const std::string&,
              float x = 0, float y = 0,
              unitsDir startDirection = unitsDir::none,
              mindStates mindState = mindStates::stand);
    
    BaseEnemy(const BaseEnemy&);
    
    virtual ~BaseEnemy();
    
    void onUpdate(double, const std::vector<std::string>&) override;
    
    void operator=(const BaseEnemy&);
    };
}

#endif /* baseEnemy_hpp */
