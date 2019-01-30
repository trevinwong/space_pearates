#include "tile_map_system.hpp"
using std::vector;

TileMapSystem::TileMapSystem()
{
	factory = TileFactory();
	// TODO: load matrix from txt file or something
	tileMap = {
		{ 0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0 },
		{ 1,1,0,0,1,1,1,0 },
		{ 0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,1 },
		{ 0,1,1,1,1,0,1,1 }
	};
}

TileMapSystem::~TileMapSystem()
{
}

void TileMapSystem::loadTileMap(glm::vec2 screen, EntityManager& entities)
{
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
			// Add a tile entity if not empty tile
			if (*col != 0) {
				entities.addEntity(factory.build(*col, 
					glm::vec2(col_i*width_tile, row_i*height_tile), 
					glm::vec2(width_tile, height_tile)));
			}
			col_i++;
		}
		col_i = 0;
		row_i++;
	}
}
