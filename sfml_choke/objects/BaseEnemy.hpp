
#ifndef baseEnemy_hpp
#define baseEnemy_hpp

#include "gameUnit.hpp"

namespace GO {
  class BaseEnemy : public GameUnit
  {
  protected:
    bool isCollised = false;
//    void colX(const std::vector<std::string>&) override;
//    void colY(const std::vector<std::string>&) override;
    
  public:
    BaseEnemy(const sf::Texture&, const std::string&, float x = 0, float y = 0);
    BaseEnemy(const std::string&, const std::string&, float x = 0, float y = 0);
    void onUpdate(double, const std::vector<std::string>&) override;
  };
}

#endif /* baseEnemy_hpp */
