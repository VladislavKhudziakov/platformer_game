
#include "CollisionObject.hpp"

namespace GO {
  
  CollisionObject::CollisionObject(char label, int x, int y)
  {
    this->label = label;
    this->x = x;
    this->y = y;
  }
  
  
  char CollisionObject::getLabel() const
  {
    return label;
  }
  
  
  sf::Vector2i CollisionObject::getPosition() const
  {
    return sf::Vector2i(x, y);
  }
}
