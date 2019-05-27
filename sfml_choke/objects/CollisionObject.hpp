
#ifndef CollisionObject_hpp
#define CollisionObject_hpp

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

namespace GO {
  struct CollisionObject
  {
  private:
    char label;
    int x;
    int y;
    
  public:
    CollisionObject(char, int, int);
    char getLabel() const;
    sf::Vector2i getPosition() const;
  };
}

#endif
