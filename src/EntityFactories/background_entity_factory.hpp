#ifndef BACKGROUND_ENTITY_FACTORY_H
#define BACKGROUND_ENTITY_FACTORY_H

#include "utility.hpp"
#include "entity.hpp"
#include "entity_manager.hpp"
#include "../Components/background_component.hpp"
#include "../Components/transform_component.hpp"
#include "../Components/color_component.hpp"

class BackgroundEntityFactory
{
public:
  static Entity createBackgroundEntity();
private:
  BackgroundEntityFactory();
};
#endif