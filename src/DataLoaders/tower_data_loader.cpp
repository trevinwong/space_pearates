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

  float relativeFirePositionX, relativeFirePositionY;
	int buildCost;
	int maxLvl;
	vector<int> upgradeCostsPerLvl;
	vector<int> attackPerLvl;
	vector<float> rangePerLvl;
	vector<float> fireRatePerLvl;
  
  fillVariable(ifs, relativeFirePositionX, "relativeFirePositionX");
  fillVariable(ifs, relativeFirePositionY, "relativeFirePositionY");
  moveToNextLine(ifs);
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

  FireTowerData ftd = FireTowerData(vec2(relativeFirePositionX, relativeFirePositionY), buildCost, maxLvl, upgradeCostsPerLvl, attackPerLvl, rangePerLvl, fireRatePerLvl);
  shared_ptr<Texture> lvl1_texture = make_shared<Texture>(texture_path("towers/fire_tower.png"), true);
  shared_ptr<Texture> lvl2_texture = make_shared<Texture>(texture_path("towers/fire_tower2.png"), true);
  shared_ptr<Texture> lvl3_texture = make_shared<Texture>(texture_path("towers/fire_tower3.png"), true);
  shared_ptr<Texture> lvl4_texture = make_shared<Texture>(texture_path("towers/fire_tower4.png"), true);
  shared_ptr<Texture> lvl5_texture = make_shared<Texture>(texture_path("towers/fire_tower5.png"), true);
  shared_ptr<Texture> lvl6_texture = make_shared<Texture>(texture_path("towers/fire_tower6.png"), true);
  ftd.towerTextures.push_back(lvl1_texture);
  ftd.towerTextures.push_back(lvl2_texture);
  ftd.towerTextures.push_back(lvl4_texture);
  ftd.towerTextures.push_back(lvl3_texture);
  ftd.towerTextures.push_back(lvl5_texture);
  ftd.towerTextures.push_back(lvl6_texture);

  return ftd;
}

LightTowerData TowerDataLoader::loadLightTowerData(string fileName)
{
  std::ifstream ifs(fileName);
  checkValidFilename(ifs, fileName);

  float relativeFirePositionX, relativeFirePositionY;
	int buildCost;
	int maxLvl;
	vector<int> upgradeCostsPerLvl;
	vector<int> attackPerLvl;
	vector<float> rangePerLvl;
	vector<float> fireRatePerLvl;
	vector<int> numProjectilesPerLvl;
  
  fillVariable(ifs, relativeFirePositionX, "relativeFirePositionX");
  fillVariable(ifs, relativeFirePositionY, "relativeFirePositionY");
  moveToNextLine(ifs);
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

  LightTowerData ltd = LightTowerData(vec2(relativeFirePositionX, relativeFirePositionY), buildCost, maxLvl, upgradeCostsPerLvl, attackPerLvl, rangePerLvl, fireRatePerLvl, numProjectilesPerLvl);

  shared_ptr<Texture> lvl1_texture = make_shared<Texture>(texture_path("towers/light_tower.png"), true);
  shared_ptr<Texture> lvl2_texture = make_shared<Texture>(texture_path("towers/light_tower2.png"), true);
  shared_ptr<Texture> lvl3_texture = make_shared<Texture>(texture_path("towers/light_tower3.png"), true);
  shared_ptr<Texture> lvl4_texture = make_shared<Texture>(texture_path("towers/light_tower4.png"), true);
  ltd.towerTextures.push_back(lvl1_texture);
  ltd.towerTextures.push_back(lvl2_texture);
  ltd.towerTextures.push_back(lvl3_texture);
  ltd.towerTextures.push_back(lvl4_texture);

  return ltd;
}

StarTowerData TowerDataLoader::loadStarTowerData(string fileName)
{
  std::ifstream ifs(fileName);
  checkValidFilename(ifs, fileName);

  float relativeFirePositionX, relativeFirePositionY;
	int buildCost;
	int maxLvl;
	vector<int> upgradeCostsPerLvl;
	vector<int> attackPerLvl;
	vector<float> rangePerLvl;
	vector<float> fireRatePerLvl;
	vector<float> sizePerLvl;
  
  fillVariable(ifs, relativeFirePositionX, "relativeFirePositionX");
  fillVariable(ifs, relativeFirePositionY, "relativeFirePositionY");
  moveToNextLine(ifs);
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

  StarTowerData std = StarTowerData(vec2(relativeFirePositionX, relativeFirePositionY), buildCost, maxLvl, upgradeCostsPerLvl, attackPerLvl, rangePerLvl, fireRatePerLvl, sizePerLvl);
  shared_ptr<Texture> lvl1_texture = make_shared<Texture>(texture_path("towers/star_tower.png"), true);
  shared_ptr<Texture> lvl2_texture = make_shared<Texture>(texture_path("towers/star_tower2.png"), true);
  shared_ptr<Texture> lvl3_texture = make_shared<Texture>(texture_path("towers/star_tower3.png"), true);
  shared_ptr<Texture> lvl4_texture = make_shared<Texture>(texture_path("towers/star_tower4.png"), true);
  shared_ptr<Texture> lvl5_texture = make_shared<Texture>(texture_path("towers/star_tower5.png"), true);
  std.towerTextures.push_back(lvl1_texture);
  std.towerTextures.push_back(lvl2_texture);
  std.towerTextures.push_back(lvl3_texture);
  std.towerTextures.push_back(lvl4_texture);
  std.towerTextures.push_back(lvl5_texture);

  return std;
}

WaterTowerData TowerDataLoader::loadWaterTowerData(string fileName)
{
  std::ifstream ifs(fileName);
  checkValidFilename(ifs, fileName);

  float relativeFirePositionX, relativeFirePositionY;
	int buildCost;
	int maxLvl;
	vector<int> upgradeCostsPerLvl;
	vector<float> slowPerLvl;
	vector<float> rangePerLvl;

  fillVariable(ifs, relativeFirePositionX, "relativeFirePositionX");
  fillVariable(ifs, relativeFirePositionY, "relativeFirePositionY");
  moveToNextLine(ifs);
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

  WaterTowerData wtd = WaterTowerData(vec2(relativeFirePositionX, relativeFirePositionY), buildCost, maxLvl, upgradeCostsPerLvl, slowPerLvl, rangePerLvl);
  shared_ptr<Texture> lvl1_texture = make_shared<Texture>(texture_path("towers/water_tower.png"), true);
  shared_ptr<Texture> lvl2_texture = make_shared<Texture>(texture_path("towers/water_tower2.png"), true);
  shared_ptr<Texture> lvl3_texture = make_shared<Texture>(texture_path("towers/water_tower3.png"), true);
  shared_ptr<Texture> lvl4_texture = make_shared<Texture>(texture_path("towers/water_tower4.png"), true);
  wtd.towerTextures.push_back(lvl1_texture);
  wtd.towerTextures.push_back(lvl2_texture);
  wtd.towerTextures.push_back(lvl3_texture);
  wtd.towerTextures.push_back(lvl4_texture);

  return wtd;
}

BoomerangTowerData TowerDataLoader::loadBoomerangTowerData(string fileName) {
  std::ifstream ifs(fileName);
  checkValidFilename(ifs, fileName);

  float relativeFirePositionX, relativeFirePositionY;
  int buildCost;
  int maxLvl;
  vector<int> upgradeCostsPerLvl;
  vector<int> attackPerLvl;
  vector<float> rangePerLvl;
  vector<float> fireRatePerLvl;

  fillVariable(ifs, relativeFirePositionX, "relativeFirePositionX");
  fillVariable(ifs, relativeFirePositionY, "relativeFirePositionY");
  moveToNextLine(ifs);
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

  BoomerangTowerData btd = BoomerangTowerData(vec2(relativeFirePositionX, relativeFirePositionY), buildCost, maxLvl,
                                              upgradeCostsPerLvl, attackPerLvl, rangePerLvl, fireRatePerLvl);

  shared_ptr<Texture> lvl1_texture = make_shared<Texture>(texture_path("towers/boomerang_tower.png"), true);
  shared_ptr<Texture> lvl2_texture = make_shared<Texture>(texture_path("towers/boomerang_tower2.png"), true);
  shared_ptr<Texture> lvl3_texture = make_shared<Texture>(texture_path("towers/boomerang_tower3.png"), true);
  shared_ptr<Texture> lvl4_texture = make_shared<Texture>(texture_path("towers/boomerang_tower4.png"), true);
  shared_ptr<Texture> lvl5_texture = make_shared<Texture>(texture_path("towers/boomerang_tower5.png"), true);
  btd.towerTextures.push_back(lvl1_texture);
  btd.towerTextures.push_back(lvl2_texture);
  btd.towerTextures.push_back(lvl3_texture);
  btd.towerTextures.push_back(lvl4_texture);
  btd.towerTextures.push_back(lvl5_texture);

  return btd;
}
