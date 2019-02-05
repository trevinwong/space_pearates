#ifndef MAP_COMPONENT_H
#define MAP_COMPONENT_H

#include "entity_manager.hpp"
#include "base_component.hpp"
#include "utility.hpp"

class MapComponent : public BaseComponent
{
public:
  MapComponent(std::vector<std::vector<int>> _mapData2DArray);
  ~MapComponent();

  static const int typeID = MAP_COMPONENT_TYPEID;
  inline virtual int getTypeID() const { return typeID; };

  int num_y_tiles;
  int num_x_tiles;
  float width_tile;
  float height_tile;
  std::vector<std::vector<int>> mapData2DArray;

private:
};

#endif
