#include "tile_map_system.hpp"

void TileMapSystem::loadTileMap(EntityManager& entities)
{
  shared_ptr<Entity> mapEntity = entities.getEntities(entities.getComponentChecker(vector<int>{ComponentType::map}))[0];
  MapComponent *mapComponent = mapEntity->getComponent<MapComponent>();
  if (mapComponent == nullptr) return;

  auto tileMap = mapComponent->mapData2DArray;
  int num_y_tiles = mapComponent->num_y_tiles;
  int num_x_tiles = mapComponent->num_x_tiles;
  float width_tile = mapComponent->width_tile;
  float height_tile = mapComponent->height_tile;
  // Is there some better way to get the indices..?
  int row_i = 0;
  int col_i = 0;
  vector<vector<char>>::iterator row;
  vector<char>::iterator col;
  for (row = tileMap.begin(); row != tileMap.end(); row++) {
    for (col = row->begin(); col != row->end(); col++) {
      if (*col == MAP_PLATFORM_TILE)
      {
        entities.addEntity(TileFactory::build(*col,
          vec2(col_i*width_tile, row_i*height_tile),
          vec2(width_tile, height_tile)));
      }
      else if (*col == MAP_BASE_POSITION) {
        Entity base = HomeFactory::createBase(vec2(col_i*width_tile, row_i*height_tile - 41.0));
        entities.addEntity(base);
      }
      else if (*col == MAP_TOWER_POSITION) {
        Entity towerBuildAreaIndicator = BuildAreaIndicatorFactory::build(
          vec2(col_i*width_tile, row_i*height_tile),
          vec2(width_tile, height_tile));
        entities.addEntity(towerBuildAreaIndicator);
      }
      /*else if (*col == MAP_PLAYER_SPAWN) {
        vec2 player_spawn = vec2(col_i*width_tile, row_i*height_tile);
        Entity player = PlayerFactory::build(player_spawn, vec2(50.0f, 65.0f));
        entities.addEntity(player);
        printVec2("(tile_map_system)player spawn:", player_spawn);
      }*/
      col_i++;
    }
    col_i = 0;
    row_i++;
  }
}
