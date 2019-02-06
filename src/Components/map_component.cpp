#include "map_component.hpp"

MapComponent::MapComponent(std::vector<std::vector<int>> _mapData2DArray) :
  mapData2DArray(_mapData2DArray)
{
  this->num_y_tiles = this->mapData2DArray.size();
  this->num_x_tiles = this->mapData2DArray.front().size();
  this->width_tile = SCREEN_WIDTH / this->num_x_tiles;
  this->height_tile = SCREEN_HEIGHT / this->num_y_tiles;
}

MapComponent::~MapComponent()
{
}
