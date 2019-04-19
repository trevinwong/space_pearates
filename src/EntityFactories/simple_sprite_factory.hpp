#ifndef SIMPLE_SPRITE_FACTORY_H
#define SIMPLE_SPRITE_FACTORY_H

#include "Utility/utility.hpp"
#include "entity.hpp"
#include "entity_manager.hpp"
#include "../Components/sprite_component.hpp"
#include "../Components/transform_component.hpp"
#include "../Components/color_component.hpp"

class SimpleSpriteFactory
{
public:
  static Entity create(string imageFile, GLboolean alpha, vec2 position, vec2 size, vec4 color);
  static Entity create();
private:
  SimpleSpriteFactory();
};
#endif