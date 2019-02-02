#include "map_entity_factory.hpp"

MapEntityFactory::MapEntityFactory()
{
}

MapEntityFactory::~MapEntityFactory()
{
}

Entity MapEntityFactory::createMapEntityFromFile(char * fileName)
{
  std::string fileNameStr(fileName);
  return createMapEntityFromFile(fileNameStr);
}

Entity MapEntityFactory::createMapEntityFromFile(std::string fileName)
{
  std::vector<std::vector<int>> tileMap2DArray = MapEntityFactory::readMapDataFile(fileName);
  MapComponent *mapComponent = new MapComponent(tileMap2DArray);

  Entity mapEntity;
  mapEntity.setComponent<MapComponent>(mapComponent);

  return mapEntity;
}

std::vector<std::vector<int>> MapEntityFactory::readMapDataFile(std::string fileName)
{
  std::ifstream mapDataFile(fileName);
  std::vector<std::vector<int>> tileMap2DArray;
  if (mapDataFile.good()) {
    while (!mapDataFile.eof()) {

      std::vector<int> tileMapData_OneRow;

      std::string line; // declare a line
      std::getline(mapDataFile, line); // read a line from file
      std::stringstream iss(line); // convert the line string to string stream

      int cellValue = -1;
      while (iss >> cellValue)
      {
        tileMapData_OneRow.push_back(cellValue);
        if (iss.peek() == ',') iss.ignore();
      }

      // ignore any empty lines
      if(tileMapData_OneRow.size() != 0)
        tileMap2DArray.push_back(tileMapData_OneRow);
    }
    // Close the file
    mapDataFile.close();
  }

  return tileMap2DArray;
}
