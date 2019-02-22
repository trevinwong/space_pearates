#ifndef WAVESET_STRUCTS_H
#define WAVESET_STRUCTS_H

#include "utility.hpp"

struct cluster {
	std::vector<glm::vec2> enemyData; //x is the enemy ID while y is the enemy amount.
};

struct wave {
	int buildPhaseTime;
	std::vector<int> spawnTimes;
	std::vector<cluster> clusters;
};
struct waveset {
	std::vector<wave> waves;
};
#endif