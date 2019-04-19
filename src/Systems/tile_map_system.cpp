#include "tile_map_system.hpp"

vector<vec2> TileMapSystem::enemySpawnPoints;
vec2 TileMapSystem::player_spawn;
vec2 TileMapSystem::home_spawn;

void TileMapSystem::loadTileMap(EntityManager & entityManager, bool drawBuildIndicators)
{
  shared_ptr<Entity> mapEntity = entityManager.getEntities(entityManager.getComponentChecker(vector<int>{ComponentType::map}))[0];
  shared_ptr<MapComponent> mapComponent = mapEntity->getComponent<MapComponent>();
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
        entityManager.addEntity(TileFactory::buildTile(
          vec2(col_i*width_tile, row_i*height_tile),
          vec2(width_tile, height_tile)));
      }
      else if (*col == MAP_BASE_POSITION) {
        home_spawn = vec2(col_i*width_tile, row_i*height_tile);
        Entity home = HomeFactory::createHome(vec2(col_i*width_tile - 100.f, row_i*height_tile - 85.f));
        entityManager.addEntity(home);
      }
      else if (*col == MAP_TOWER_POSITION && drawBuildIndicators) {
        Entity towerBuildAreaIndicator = TileFactory::buildTowerAreaIndicator(
          vec2(col_i*width_tile, row_i*height_tile),
          vec2(width_tile, height_tile));
        entityManager.addEntity(towerBuildAreaIndicator);
      }
      else if (*col == MAP_PLAYER_SPAWN) {
        player_spawn = vec2(col_i*width_tile, row_i*height_tile);
      }
      else if (*col == MAP_ENEMY_SPAWN) {
        enemySpawnPoints.push_back(vec2(col_i*width_tile, row_i*height_tile));
      }
      col_i++;
    }
    col_i = 0;
    row_i++;
  }
  mapComponent->enemySpawnPoints = enemySpawnPoints;
}
