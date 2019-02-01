#ifndef BASE_H
#define BASE_H

#include <vector>
#include "utility.hpp"
#include "sprite_system.hpp"

class Base
{
  public:

    Base(glm::vec2 posn);
    ~Base();

    // posn in window coordinate system (origin is at top left)
    glm::vec2 getPosition() const;

    bool isAlive() const;


    // Called when projectile collides with Base
    void wasHit();

  private:

    glm::vec2 position;
    int health;
};
#endif 
