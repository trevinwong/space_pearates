#ifndef MAP_ENTITY_FACTORY_H
#define MAP_ENTITY_FACTORY_H

#include "Utility/utility.hpp"
#include "entity_manager.hpp"
#include "../Components/map_component.hpp"

class MapEntityFactory
{
public:
  static Entity createMapEntityFromFile(char* fileName);
  static Entity createMapEntityFromFile(string fileName);

private:
  MapEntityFactory();
  static vector<vector<char>> readMapDataFile(string fileName);
};

#endif
