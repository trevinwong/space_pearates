#ifndef MAP_ENTITY_FACTORY_H
#define MAP_ENTITY_FACTORY_H

#include <iostream>
#include <fstream>
#include <sstream>
#include "entity_manager.hpp"
#include "map_component.hpp"
#include "utility.hpp"

class MapEntityFactory
{
public:
  ~MapEntityFactory();
  static Entity createMapEntityFromFile(char* fileName);
  static Entity createMapEntityFromFile(std::string fileName);

private:
  MapEntityFactory();
  static std::vector<std::vector<int>> readMapDataFile(std::string fileName);
};

#endif