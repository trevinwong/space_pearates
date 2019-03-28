#include "tower_data_loader.hpp"


unordered_map<TOWER_UI_OPT_TYPE, shared_ptr<TowerData>> TowerDataLoader::allTowerData = unordered_map<TOWER_UI_OPT_TYPE, shared_ptr<TowerData>>{};

void TowerDataLoader::loadTowerData()
{
	allTowerData[BUILD_FIRE_TOWER] = make_shared<FireTowerData>(loadFireTowerData(towers_path("fire_tower_data.txt")));
	allTowerData[BUILD_LIGHT_TOWER] = make_shared<LightTowerData>(loadLightTowerData(towers_path("light_tower_data.txt")));
	allTowerData[BUILD_STAR_TOWER] = make_shared<StarTowerData>(loadStarTowerData(towers_path("star_tower_data.txt")));
	allTowerData[BUILD_WATER_TOWER] = make_shared<WaterTowerData>(loadWaterTowerData(towers_path("water_tower_data.txt")));
	allTowerData[BUILD_BOOMERANG_TOWER] = make_shared<BoomerangTowerData>(loadBoomerangTowerData(towers_path("boomerang_tower_data.txt")));
}

FireTowerData TowerDataLoader::loadFireTowerData(string fileName)
{
  std::ifstream ifs(fileName);
  checkValidFilename(ifs, fileName);

	int buildCost;
	int maxLvl;
	vector<int> upgradeCostsPerLvl;
	vector<int> attackPerLvl;
	vector<float> rangePerLvl;
	vector<float> fireRatePerLvl;
  
  fillVariable(ifs, buildCost, "buildCost");
  moveToNextLine(ifs);
  fillVariable(ifs, maxLvl, "maxLvl");
  moveToNextLine(ifs);
  fillVector(ifs, upgradeCostsPerLvl, maxLvl + 1, "upgradeCost");
  moveToNextLine(ifs);
  fillVector(ifs, attackPerLvl, maxLvl + 1, "attack");
  moveToNextLine(ifs);
  fillVector(ifs, rangePerLvl, maxLvl + 1, "range");
  moveToNextLine(ifs);
  fillVector(ifs, fireRatePerLvl, maxLvl + 1, "fireRate");
  
  ifs.close();
  return FireTowerData(buildCost, maxLvl, upgradeCostsPerLvl, attackPerLvl, rangePerLvl, fireRatePerLvl);
}

LightTowerData TowerDataLoader::loadLightTowerData(string fileName)
{
  std::ifstream ifs(fileName);
  checkValidFilename(ifs, fileName);

	int buildCost;
	int maxLvl;
	vector<int> upgradeCostsPerLvl;
	vector<int> attackPerLvl;
	vector<float> rangePerLvl;
	vector<float> fireRatePerLvl;
	vector<int> numProjectilesPerLvl;
  
  fillVariable(ifs, buildCost, "buildCost");
  moveToNextLine(ifs);
  fillVariable(ifs, maxLvl, "maxLvl");
  moveToNextLine(ifs);
  fillVector(ifs, upgradeCostsPerLvl, maxLvl + 1, "upgradeCost");
  moveToNextLine(ifs);
  fillVector(ifs, attackPerLvl, maxLvl + 1, "attack");
  moveToNextLine(ifs);
  fillVector(ifs, rangePerLvl, maxLvl + 1, "range");
  moveToNextLine(ifs);
  fillVector(ifs, fireRatePerLvl, maxLvl + 1, "fireRate");
  moveToNextLine(ifs);
  fillVector(ifs, numProjectilesPerLvl, maxLvl + 1, "numProjectiles");
  
  ifs.close();
  return LightTowerData(buildCost, maxLvl, upgradeCostsPerLvl, attackPerLvl, rangePerLvl, fireRatePerLvl, numProjectilesPerLvl);
}

StarTowerData TowerDataLoader::loadStarTowerData(string fileName)
{
  std::ifstream ifs(fileName);
  checkValidFilename(ifs, fileName);

	int buildCost;
	int maxLvl;
	vector<int> upgradeCostsPerLvl;
	vector<int> attackPerLvl;
	vector<float> rangePerLvl;
	vector<float> fireRatePerLvl;
	vector<float> sizePerLvl;
  
  fillVariable(ifs, buildCost, "buildCost");
  moveToNextLine(ifs);
  fillVariable(ifs, maxLvl, "maxLvl");
  moveToNextLine(ifs);
  fillVector(ifs, upgradeCostsPerLvl, maxLvl + 1, "upgradeCost");
  moveToNextLine(ifs);
  fillVector(ifs, attackPerLvl, maxLvl + 1, "attack");
  moveToNextLine(ifs);
  fillVector(ifs, rangePerLvl, maxLvl + 1, "range");
  moveToNextLine(ifs);
  fillVector(ifs, fireRatePerLvl, maxLvl + 1, "fireRate");
  moveToNextLine(ifs);
  fillVector(ifs, sizePerLvl, maxLvl + 1, "size");
  
  ifs.close();
  return StarTowerData(buildCost, maxLvl, upgradeCostsPerLvl, attackPerLvl, rangePerLvl, fireRatePerLvl, sizePerLvl);
}

WaterTowerData TowerDataLoader::loadWaterTowerData(string fileName)
{
  std::ifstream ifs(fileName);
  checkValidFilename(ifs, fileName);

	int buildCost;
	int maxLvl;
	vector<int> upgradeCostsPerLvl;
	vector<float> slowPerLvl;
	vector<float> rangePerLvl;

  fillVariable(ifs, buildCost, "buildCost");
  moveToNextLine(ifs);
  fillVariable(ifs, maxLvl, "maxLvl");
  moveToNextLine(ifs);
  fillVector(ifs, upgradeCostsPerLvl, maxLvl + 1, "upgradeCost");
  moveToNextLine(ifs);
  fillVector(ifs, slowPerLvl, maxLvl + 1, "slow");
  moveToNextLine(ifs);
  fillVector(ifs, rangePerLvl, maxLvl + 1, "range");
  
  ifs.close();
  return WaterTowerData(buildCost, maxLvl, upgradeCostsPerLvl, slowPerLvl, rangePerLvl);
}

BoomerangTowerData TowerDataLoader::loadBoomerangTowerData(string fileName)
{
  std::ifstream ifs(fileName);
  checkValidFilename(ifs, fileName);

	int buildCost;
	int maxLvl;
	vector<int> upgradeCostsPerLvl;
	vector<int> attackPerLvl;
	vector<float> rangePerLvl;
	vector<float> fireRatePerLvl;
  
  fillVariable(ifs, buildCost, "buildCost");
  moveToNextLine(ifs);
  fillVariable(ifs, maxLvl, "maxLvl");
  moveToNextLine(ifs);
  fillVector(ifs, upgradeCostsPerLvl, maxLvl + 1, "upgradeCost");
  moveToNextLine(ifs);
  fillVector(ifs, attackPerLvl, maxLvl + 1, "attack");
  moveToNextLine(ifs);
  fillVector(ifs, rangePerLvl, maxLvl + 1, "range");
  moveToNextLine(ifs);
  fillVector(ifs, fireRatePerLvl, maxLvl + 1, "fireRate");
  
  ifs.close();
  return BoomerangTowerData(buildCost, maxLvl, upgradeCostsPerLvl, attackPerLvl, rangePerLvl, fireRatePerLvl);
}
