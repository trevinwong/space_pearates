#ifndef TILE_FACTORY_H
#define TILE_FACTORY_H

#include "entity.hpp"
#include "program.hpp"
#include "sprite_component.hpp"
#include "transform_component.hpp"
#include "color_component.hpp"

class TileFactory
{
public:
  TileFactory();
  ~TileFactory();
  // Build either empty tile (0) or platform tile (1)
  Entity build(int type, glm::vec2 position, glm::vec2 scale);
};

#endif