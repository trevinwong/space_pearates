#ifndef BASE_H
#define BASE_H

#include <vector>
#include "utility.hpp"
#include "entity.hpp"
#include "entity_manager.hpp"
#include "sprite_system.hpp"

class BaseFactory
{
  public:
    static Entity createBase(glm::vec2 position);
  private:
    BaseFactory();
};
#endif BASE_H