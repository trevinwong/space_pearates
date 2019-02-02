#ifndef TILE_MAP_SYSTEM_H
#define TILE_MAP_SYSTEM_H

#include "entity_manager.hpp"
#include "tile_factory.hpp"
#include "map_component.hpp"
#include "../Tower/tower_entity_factory.hpp"
#include "../Base/base_factory.hpp"

class TileMapSystem
{
public:
  TileMapSystem();
  ~TileMapSystem();

  void loadTileMap(EntityManager& entities);

private:
  TileFactory factory;
};

#endif