#ifndef TILE_MAP_SYSTEM_H
#define TILE_MAP_SYSTEM_H

#include "utility.hpp"
#include "entity_manager.hpp"
#include "../Components/map_component.hpp"
#include "../EntityFactories/tile_factory.hpp"
#include "../EntityFactories/tower_entity_factory.hpp"
#include "EntityFactories/home_factory.hpp"
#include "../EntityFactories/player_factory.hpp"

class TileMapSystem
{
public:
  void loadTileMap(EntityManager &entityManager);

private:
  TileFactory factory;
};

#endif
