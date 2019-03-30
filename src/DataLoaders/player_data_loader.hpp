#ifndef PLAYER_DATA_H
#define PLAYER_DATA_H

#include "Utility/utility.hpp"
#include "data_loading_utility.hpp"
#include "player_structs.hpp"

class PlayerDataLoader {
	public:
		static void loadPlayerData();
    static PlayerData playerData;
};

#endif
