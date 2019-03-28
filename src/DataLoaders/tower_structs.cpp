#include "tower_structs.hpp"

TowerData::TowerData()
{
}

TowerData::TowerData(vec2 _relativeFirePosition, int _buildCost, int _maxLvl, vector<int> _upgradeCostsPerLvl) :
	relativeFirePosition(_relativeFirePosition), buildCost(_buildCost), maxLvl(_maxLvl), upgradeCostsPerLvl(_upgradeCostsPerLvl)
{
}

FireTowerData::FireTowerData(vec2 _relativeFirePosition, int _buildCost, int _maxLvl, vector<int> _upgradeCostsPerLvl, vector<int> _attackPerLvl, vector<float> _rangePerLvl, vector<float> _fireRatePerLvl) :
	TowerData(_relativeFirePosition, _buildCost, _maxLvl, _upgradeCostsPerLvl), attackPerLvl(_attackPerLvl), rangePerLvl(_rangePerLvl), fireRatePerLvl(_fireRatePerLvl)
{
}

LightTowerData::LightTowerData(vec2 _relativeFirePosition, int _buildCost, int _maxLvl, vector<int> _upgradeCostsPerLvl, vector<int> _attackPerLvl, vector<float> _rangePerLvl, vector<float> _fireRatePerLvl, vector<int> _numProjectilesPerLvl) :
	TowerData(_relativeFirePosition, _buildCost, _maxLvl, _upgradeCostsPerLvl), attackPerLvl(_attackPerLvl), rangePerLvl(_rangePerLvl), fireRatePerLvl(_fireRatePerLvl), numProjectilesPerLvl(_numProjectilesPerLvl)
{
}

StarTowerData::StarTowerData(vec2 _relativeFirePosition, int _buildCost, int _maxLvl, vector<int> _upgradeCostsPerLvl, vector<int> _attackPerLvl, vector<float> _rangePerLvl, vector<float> _fireRatePerLvl, vector<float> _sizePerLvl) :
	TowerData(_relativeFirePosition, _buildCost, _maxLvl, _upgradeCostsPerLvl), attackPerLvl(_attackPerLvl), rangePerLvl(_rangePerLvl), fireRatePerLvl(_fireRatePerLvl), sizePerLvl(_sizePerLvl)
{
}

WaterTowerData::WaterTowerData(vec2 _relativeFirePosition, int _buildCost, int _maxLvl, vector<int> _upgradeCostsPerLvl, vector<float> _slowPerLvl, vector<float> _rangePerLvl) :
  TowerData(_relativeFirePosition, _buildCost, _maxLvl, _upgradeCostsPerLvl), slowPerLvl(_slowPerLvl), rangePerLvl(_rangePerLvl)
{
}

BoomerangTowerData::BoomerangTowerData(vec2 _relativeFirePosition, int _buildCost, int _maxLvl, vector<int> _upgradeCostsPerLvl, vector<int> _attackPerLvl, vector<float> _rangePerLvl, vector<float> _fireRatePerLvl) :
  TowerData(_relativeFirePosition, _buildCost, _maxLvl, _upgradeCostsPerLvl), attackPerLvl(_attackPerLvl), rangePerLvl(_rangePerLvl), fireRatePerLvl(_fireRatePerLvl)
{
}
