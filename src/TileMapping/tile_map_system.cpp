#include "tile_map_system.hpp"
using std::vector;

TileMapSystem::TileMapSystem()
{
  factory = TileFactory();
}

TileMapSystem::~TileMapSystem()
{
}

void TileMapSystem::loadTileMap(EntityManager& entities)
{
<<<<<<< HEAD
  int num_y_tiles = tileMap.size();
  int num_x_tiles = tileMap.front().size();
  float width_tile = screen.x / num_x_tiles;
  float height_tile = screen.y / num_y_tiles;
  // Is there some better way to get the indices..?
  int row_i = 0;
  int col_i = 0;
  vector<vector<int>>::iterator row;
  vector<int>::iterator col;
  for (row = tileMap.begin(); row != tileMap.end(); row++) {
    for (col = row->begin(); col != row->end(); col++) {
      // here build some test towers if position is 2
      // TODO: if the block is 2, then put an invisible building area block
      if (*col == 2) {
        // TODO: remove those test before merge
        // tower1 test
        Entity tower = TowerEntityFactory::createTower(glm::vec2(col_i*width_tile + width_tile / 2.0, row_i*height_tile + height_tile), glm::vec2(25.0f, 50.0f));
        entities.addEntity(tower);
      }
      // end tower build
      // Add a tile entity if not empty tile
      if (*col == 1) {
        entities.addEntity(factory.build(*col,
          glm::vec2(col_i*width_tile, row_i*height_tile),
          glm::vec2(width_tile, height_tile)));
=======
      }
      col_i = 0;
      row_i++;
    }
  }
}
