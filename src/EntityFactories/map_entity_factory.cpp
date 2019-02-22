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
  std::vector<std::vector<char>> tileMap2DArray = MapEntityFactory::readMapDataFile(fileName);
  MapComponent *mapComponent = new MapComponent(tileMap2DArray);

  Entity mapEntity;
  mapEntity.setComponent<MapComponent>(mapComponent);

  return mapEntity;
}

std::vector<std::vector<char>> MapEntityFactory::readMapDataFile(std::string fileName)
{
  std::ifstream mapDataFile(fileName);
  std::vector<std::vector<char>> tileMap2DArray;
  if (mapDataFile.good()) {
    while (!mapDataFile.eof()) {

      std::vector<char> tileMapData_OneRow;

      std::string line; // declare a line
      std::getline(mapDataFile, line); // read a line from file
      std::stringstream iss(line); // convert the line string to string stream

      char cellValue = 0;
      while (iss >> cellValue)
      {
        tileMapData_OneRow.push_back(cellValue);
        if (iss.peek() == ',' || iss.peek() == ' ') iss.ignore();   // comma for csv file, space for copying from google sheet
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
