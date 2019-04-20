#ifndef TOWER_STRUCTS_H
#define TOWER_STRUCTS_H

#include <Utility/texture.hpp>
#include "Utility/utility.hpp"

class TowerData {
	public:
    vec2 relativeFirePosition;
		int buildCost;
		int maxLvl;
		vector<int> upgradeCostsPerLvl; // you start at level 0
	vector<shared_ptr<Texture>> towerTextures;
	TowerData();
    virtual ~TowerData() = default;
		TowerData(vec2 _relativeFirePosition, int buildCost, int maxLvl, vector<int> upgradeCostsPerLvl);
};

class FireTowerData : public TowerData {
	public:
		vector<int> attackPerLvl;
		vector<float> rangePerLvl;
		vector<float> fireRatePerLvl;
		FireTowerData(vec2 _relativeFirePosition, int buildCost, int maxLvl, vector<int> upgradeCostsPerLvl, vector<int> attackPerLvl, vector<float> rangePerLvl, vector<float> fireRatePerLvl);
};

class LightTowerData : public TowerData {
	public:
		vector<int> attackPerLvl;
		vector<float> rangePerLvl;
		vector<float> fireRatePerLvl;
		vector<int> numProjectilesPerLvl;
		LightTowerData(vec2 _relativeFirePosition, int buildCost, int maxLvl, vector<int> upgradeCostsPerLvl, vector<int> attackPerLvl, vector<float> rangePerLvl, vector<float> fireRatePerLvl, vector<int> numProjectilesPerLvl);
};

class StarTowerData : public TowerData {
	public:
		vector<int> attackPerLvl;
		vector<float> rangePerLvl;
		vector<float> fireRatePerLvl;
		vector<float> sizePerLvl;
		StarTowerData(vec2 _relativeFirePosition, int buildCost, int maxLvl, vector<int> upgradeCostsPerLvl, vector<int> attackPerLvl, vector<float> rangePerLvl, vector<float> fireRatePerLvl, vector<float> sizePerLvl);
};

class WaterTowerData : public TowerData {
	public:
		vector<float> slowPerLvl;
		vector<float> rangePerLvl;
		WaterTowerData(vec2 _relativeFirePosition, int buildCost, int maxLvl, vector<int> upgradeCostsPerLvl, vector<float> slowPerLvl, vector<float> rangePerLvl);
};

class BoomerangTowerData : public TowerData {
	public:
		vector<int> attackPerLvl;
		vector<float> rangePerLvl;
		vector<float> fireRatePerLvl;
		BoomerangTowerData(vec2 _relativeFirePosition, int buildCost, int maxLvl, vector<int> upgradeCostsPerLvl, vector<int> attackPerLvl, vector<float> rangePerLvl, vector<float> fireRatePerLvl);
};

#endif
