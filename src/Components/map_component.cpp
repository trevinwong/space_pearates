#include "map_component.hpp"

MapComponent::MapComponent(vector<vector<char>> _mapData2DArray) :
  mapData2DArray(_mapData2DArray)
{
  this->num_y_tiles = this->mapData2DArray.size();
  this->num_x_tiles = this->mapData2DArray.front().size();
  this->width_tile = (float)SCREEN_WIDTH / (float)this->num_x_tiles;
  this->height_tile = (float)SCREEN_HEIGHT / (float)this->num_y_tiles;

  reset();
}

void MapComponent::reset() {
  // initial a blank map for tower distribution
  // towerDistributionMap[row][col] or towerDistributionMap[y][x]
  this->towerDistributionMap = vector<vector<TOWER_ID>>(num_y_tiles, vector<TOWER_ID>(num_x_tiles, NO_TOWER_BUILD_HERE));
}

bool MapComponent::isTowerAt(float x, float y)
{
  int i = (int)(x / width_tile);
  int j = (int)(y / height_tile);
  return isTowerAt(i, j);
}

bool MapComponent::isTowerAt(int i, int j)
{
  if (i < 0 || i >= num_x_tiles || j < 0 || j >= num_y_tiles) return false;
  return this->towerDistributionMap[j][i] != NO_TOWER_BUILD_HERE;
}

bool MapComponent::canBuildTowerAt(float x, float y)
{
  int i = (int)(x / width_tile);
  int j = (int)(y / height_tile);
  return canBuildTowerAt(i, j);
}

bool MapComponent::canBuildTowerAt(int col, int row)
{
  // check row below is a platform tile
  if (col < 0 || col >= num_x_tiles || row+1 < 0 || row+1 >= num_y_tiles) return false;
  return this->mapData2DArray[row+1][col] == MAP_PLATFORM_TILE;
}

void MapComponent::buildTowerAt(TOWER_ID towerId, float x, float y)
{
  int i = (int)(x / width_tile);
  int j = (int)(y / height_tile);
  return buildTowerAt(towerId, i, j);
}

void MapComponent::buildTowerAt(TOWER_ID towerId, int col, int row)
{
  if (col < 0 || col >= num_x_tiles || row < 0 || row >= num_y_tiles) return;
  this->towerDistributionMap[row][col] = towerId;
}

TOWER_ID MapComponent::getTowerIdAt(float x, float y)
{
  int col = (int)(x / width_tile);
  int row = (int)(y / height_tile);
  return getTowerIdAt(col, row);
}

TOWER_ID MapComponent::getTowerIdAt(int col, int row)
{
  if (col < 0 || col >= num_x_tiles || row < 0 || row >= num_y_tiles) return NO_TOWER_BUILD_HERE;
  return this->towerDistributionMap[row][col];
}

void MapComponent::removeTowerAt(float x, float y)
{
  int col = (int)(x / width_tile);
  int row = (int)(y / height_tile);
  return removeTowerAt(col, row);
}

void MapComponent::removeTowerAt(int col, int row)
{
  if (col < 0 || col >= num_x_tiles || row < 0 || row >= num_y_tiles) return;
  this->towerDistributionMap[row][col] = NO_TOWER_BUILD_HERE;
}
