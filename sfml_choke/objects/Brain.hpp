
#ifndef Brain_hpp
#define Brain_hpp

#include "BaseEnemy.hpp"

namespace GO {
  class Brain
  {
    const GameUnit* owner;
    
  public:
    Brain(const GameUnit* owner);
  };
}

#endif /* Brain_hpp */
