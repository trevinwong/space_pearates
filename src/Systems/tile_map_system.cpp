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
    // find the mapEntity from the entity list
    vector<shared_ptr<Entity>> entityList = entities.getEntities();
    for (shared_ptr<Entity> e : entityList)
    {
        MapComponent *mapComponent = e->getComponent<MapComponent>();
        if (mapComponent == nullptr) continue;

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
                    entities.addEntity(factory.build(*col,
                                                     glm::vec2(col_i*width_tile, row_i*height_tile),
                                                     glm::vec2(width_tile, height_tile)));
                }
                else if (*col == MAP_BASE_POSITION) {
                    Entity base = BaseFactory::createBase(glm::vec2(col_i*width_tile, row_i*height_tile-41.0));
                    entities.addEntity(base);
                }
                col_i++;
            }
            col_i = 0;
            row_i++;
        }
    }
}
