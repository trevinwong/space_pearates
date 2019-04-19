#ifndef HOME_FACTORY_H
#define HOME_FACTORY_H

#include "Utility/utility.hpp"
#include "entity.hpp"
#include "entity_manager.hpp"
#include "Systems/sprite_system.hpp"
#include "Components/health_component.hpp"
#include "Components/home_component.hpp"

class HomeFactory
{
public:
  static Entity createHome(vec2 position);
private:
  HomeFactory();
};
#endif