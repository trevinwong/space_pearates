#ifndef TOWER_DATA_H
#define TOWER_DATA_H

#include "Utility/utility.hpp"
#include "data_loading_utility.hpp"
#include "tower_structs.hpp"

class TowerDataLoader {
	public:
		static void loadTowerData();
		static FireTowerData loadFireTowerData(string fileName);
		static LightTowerData loadLightTowerData(string fileName);
		static StarTowerData loadStarTowerData(string fileName);
		static WaterTowerData loadWaterTowerData(string fileName);
		static BoomerangTowerData loadBoomerangTowerData(string fileName);
		static unordered_map<TOWER_UI_OPT_TYPE, shared_ptr<TowerData>> allTowerData;
};

#endif
