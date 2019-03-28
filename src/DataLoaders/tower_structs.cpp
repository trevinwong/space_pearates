#include "tower_structs.hpp"

TowerData::TowerData()
{
}

TowerData::TowerData(int _buildCost, int _maxLvl, vector<int> _upgradeCostsPerLvl) :
	buildCost(_buildCost), maxLvl(_maxLvl), upgradeCostsPerLvl(_upgradeCostsPerLvl)
{
}

FireTowerData::FireTowerData(int _buildCost, int _maxLvl, vector<int> _upgradeCostsPerLvl, vector<int> _attackPerLvl, vector<float> _rangePerLvl, vector<float> _fireRatePerLvl) :
	TowerData(_buildCost, _maxLvl, _upgradeCostsPerLvl), attackPerLvl(_attackPerLvl), rangePerLvl(_rangePerLvl), fireRatePerLvl(_fireRatePerLvl)
{
}

LightTowerData::LightTowerData(int _buildCost, int _maxLvl, vector<int> _upgradeCostsPerLvl, vector<int> _attackPerLvl, vector<float> _rangePerLvl, vector<float> _fireRatePerLvl, vector<int> _numProjectilesPerLvl) :
	TowerData(_buildCost, _maxLvl, _upgradeCostsPerLvl), attackPerLvl(_attackPerLvl), rangePerLvl(_rangePerLvl), fireRatePerLvl(_fireRatePerLvl), numProjectilesPerLvl(_numProjectilesPerLvl)
{
}

StarTowerData::StarTowerData(int _buildCost, int _maxLvl, vector<int> _upgradeCostsPerLvl, vector<int> _attackPerLvl, vector<float> _rangePerLvl, vector<float> _fireRatePerLvl, vector<float> _sizePerLvl) :
	TowerData(_buildCost, _maxLvl, _upgradeCostsPerLvl), attackPerLvl(_attackPerLvl), rangePerLvl(_rangePerLvl), fireRatePerLvl(_fireRatePerLvl), sizePerLvl(_sizePerLvl)
{
}

WaterTowerData::WaterTowerData(int _buildCost, int _maxLvl, vector<int> _upgradeCostsPerLvl, vector<float> _slowPerLvl, vector<float> _rangePerLvl) :
  TowerData(_buildCost, _maxLvl, _upgradeCostsPerLvl), slowPerLvl(_slowPerLvl), rangePerLvl(_rangePerLvl)
{
}

BoomerangTowerData::BoomerangTowerData(int _buildCost, int _maxLvl, vector<int> _upgradeCostsPerLvl, vector<int> _attackPerLvl, vector<float> _rangePerLvl, vector<float> _fireRatePerLvl) :
  TowerData(_buildCost, _maxLvl, _upgradeCostsPerLvl), attackPerLvl(_attackPerLvl), rangePerLvl(_rangePerLvl), fireRatePerLvl(_fireRatePerLvl)
{
}
