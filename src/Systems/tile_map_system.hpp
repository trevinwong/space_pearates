#ifndef TILE_MAP_SYSTEM_H
#define TILE_MAP_SYSTEM_H

#include "entity_manager.hpp"
#include "../EntityFactories/tile_factory.hpp"
#include "../Components/map_component.hpp"
#include "../EntityFactories/tower_entity_factory.hpp"
#include "../EntityFactories/base_factory.hpp"

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
