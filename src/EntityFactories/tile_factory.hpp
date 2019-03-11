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
  static Entity buildTile(vec2 position, vec2 scale);
  static Entity buildTowerAreaIndicator(vec2 position, vec2 scale);
};

#endif
