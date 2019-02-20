#ifndef BASE_H
#define BASE_H

#include <vector>
#include "utility.hpp"
#include "entity.hpp"
#include "entity_manager.hpp"
#include "Systems/sprite_system.hpp"
#include "Components/health_component.hpp"

class BaseFactory
{
  public:
    static Entity createBase(glm::vec2 position);
  private:
    BaseFactory();
};
#endif