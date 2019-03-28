#ifndef TOWER_STRUCTS_H
#define TOWER_STRUCTS_H

#include "Utility/utility.hpp"

class TowerData {
	public:
		int buildCost;
		int maxLvl;
		vector<int> upgradeCostsPerLvl; // you start at level 0
    TowerData();
    virtual ~TowerData() = default;
		TowerData(int buildCost, int maxLvl, vector<int> upgradeCostsPerLvl);
};

class FireTowerData : public TowerData {
	public:
		vector<int> attackPerLvl;
		vector<float> rangePerLvl;
		vector<float> fireRatePerLvl;
		FireTowerData(int buildCost, int maxLvl, vector<int> upgradeCostsPerLvl, vector<int> attackPerLvl, vector<float> rangePerLvl, vector<float> fireRatePerLvl);
};

class LightTowerData : public TowerData {
	public:
		vector<int> attackPerLvl;
		vector<float> rangePerLvl;
		vector<float> fireRatePerLvl;
		vector<int> numProjectilesPerLvl;
		LightTowerData(int buildCost, int maxLvl, vector<int> upgradeCostsPerLvl, vector<int> attackPerLvl, vector<float> rangePerLvl, vector<float> fireRatePerLvl, vector<int> numProjectilesPerLvl);
};

class StarTowerData : public TowerData {
	public:
		vector<int> attackPerLvl;
		vector<float> rangePerLvl;
		vector<float> fireRatePerLvl;
		vector<float> sizePerLvl;
		StarTowerData(int buildCost, int maxLvl, vector<int> upgradeCostsPerLvl, vector<int> attackPerLvl, vector<float> rangePerLvl, vector<float> fireRatePerLvl, vector<float> sizePerLvl);
};

class WaterTowerData : public TowerData {
	public:
		vector<float> slowPerLvl;
		vector<float> rangePerLvl;
		WaterTowerData(int buildCost, int maxLvl, vector<int> upgradeCostsPerLvl, vector<float> slowPerLvl, vector<float> rangePerLvl);
};

class BoomerangTowerData : public TowerData {
	public:
		vector<int> attackPerLvl;
		vector<float> rangePerLvl;
		vector<float> fireRatePerLvl;
		BoomerangTowerData(int buildCost, int maxLvl, vector<int> upgradeCostsPerLvl, vector<int> attackPerLvl, vector<float> rangePerLvl, vector<float> fireRatePerLvl);
};

#endif
