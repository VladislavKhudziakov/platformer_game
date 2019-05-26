
#ifndef baseEnemy_hpp
#define baseEnemy_hpp

#include "gameUnit.hpp"

namespace GO {
  class BaseEnemy : public GameUnit
  {
  protected:
    void colX(const std::vector<std::string>&) override;
    void colY(const std::vector<std::string>&) override;
    
  public:
    BaseEnemy(const sf::Texture& tex, const std::string& name, float x, float y) : GameUnit(tex, name, x, y) { };
    BaseEnemy(const std::string& texName, const std::string& name, float x, float y) : GameUnit(texName, name, x, y) { };
  };
}

#endif /* baseEnemy_hpp */
