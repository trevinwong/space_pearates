#ifndef TILE_FACTORY_H
#define TILE_FACTORY_H

#include "entity.hpp"
#include "program.hpp"
#include "Components/tile_component.hpp"
#include "Components/sprite_component.hpp"
#include "Components/transform_component.hpp"
#include "Components/color_component.hpp"
#include "Components/collision_component.hpp"

class TileFactory
{
public:
  // Build either empty tile (0) or platform tile (1)
  static Entity build(int type, glm::vec2 position, glm::vec2 scale);
};

#endif
