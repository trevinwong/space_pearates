#include "map_entity_factory.hpp"

Entity MapEntityFactory::createMapEntityFromFile(char * fileName)
{
  string fileNameStr(fileName);
  return createMapEntityFromFile(fileNameStr);
}

Entity MapEntityFactory::createMapEntityFromFile(std::string fileName)
{
  vector<vector<char>> tileMap2DArray = MapEntityFactory::readMapDataFile(fileName);
  shared_ptr<MapComponent> mapComponent = make_shared<MapComponent>(tileMap2DArray);

  Entity mapEntity;
  mapEntity.setComponent<MapComponent>(mapComponent);
  return mapEntity;
}

vector<vector<char>> MapEntityFactory::readMapDataFile(string fileName)
{
  std::ifstream mapDataFile(fileName);
  vector<vector<char>> tileMap2DArray;
  if (mapDataFile.good()) {
    while (!mapDataFile.eof()) {

      vector<char> tileMapData_OneRow;

      string line; // declare a line
      std::getline(mapDataFile, line); // read a line from file
      std::stringstream iss(line); // convert the line string to string stream

      char cellValue = 0;
      while (iss >> cellValue)
      {
        tileMapData_OneRow.push_back(cellValue);
        if (iss.peek() == ',' || iss.peek() == ' ') iss.ignore();   // comma for csv file, space for copying from google sheet
      }

      // ignore any empty lines
      if (tileMapData_OneRow.size() != 0)
        tileMap2DArray.push_back(tileMapData_OneRow);
    }
    // Close the file
    mapDataFile.close();
  }

  return tileMap2DArray;
}
