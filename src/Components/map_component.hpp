#ifndef MAP_COMPONENT_H
#define MAP_COMPONENT_H

#include "entity_manager.hpp"
#include "base_component.hpp"
#include "Utility/utility.hpp"

class MapComponent : public BaseComponent
{
public:
  MapComponent(vector<vector<char>> _mapData2DArray);
  void reset();

  static const int typeID = ComponentType::map;
  inline virtual int getTypeID() const { return typeID; };

  int num_y_tiles;
  int num_x_tiles;
  float width_tile;
  float height_tile;
  vector<vector<char>> mapData2DArray;
  vector<vector<TOWER_ID>> towerDistributionMap;
  vector<vec2> enemySpawnPoints;

  /*
    For those func below, x and y are screen coords, col and row are 2D vector indexes
  */
  // if a tower is already built at a given pos, then retrun true
  bool isTowerAt(float x, float y);
  bool isTowerAt(int col, int row);
  // check mapData2DArray if a position can build a tower
  bool canBuildTowerAt(float x, float y);
  bool canBuildTowerAt(int col, int row);
  // build a tower in the map, add the tower entity id to towerDistributionMap
  void buildTowerAt(TOWER_ID towerId, float x, float y);
  void buildTowerAt(TOWER_ID towerId, int col, int row);
  // return tower entity id, if no tower there, then return -1 since no entity id == -1
  TOWER_ID getTowerIdAt(float x, float y);
  TOWER_ID getTowerIdAt(int col, int row);
  // remove a tower from map, this operation only effect towerDistributionMap variable
  void removeTowerAt(float x, float y);
  void removeTowerAt(int col, int row);
private:
};

#endif
