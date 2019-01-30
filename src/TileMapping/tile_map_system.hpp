#ifndef TILE_MAP_SYSTEM_H
#define TILE_MAP_SYSTEM_H

#include "entity_manager.hpp"
#include "tile_factory.hpp"

class TileMapSystem
{
public:
	TileMapSystem();
	~TileMapSystem();
	void loadTileMap(glm::vec2 screen, EntityManager& entities);

private:
	TileFactory factory;
	std::vector<std::vector<int>> tileMap;
};

#endif