#ifndef WAVESET_STRUCTS_H
#define WAVESET_STRUCTS_H

#include "utility.hpp"

class Cluster {
public:
	vector<vec2> enemyData; //x is the enemy ID while y is the enemy amount.
	Cluster(vector<vec2> _enemyData);
};

class Wave {
public:
	int buildPhaseTime;
	vector<int> spawnTimes;
	vector<Cluster> clusters;
	int totalEnemies = 0;
	Wave(int _buildPhaseTime, vector<int> _spawnTimes, vector<Cluster> _clusters);
};

class Waveset {
public:
	vector<Wave> waves;
	Waveset(vector<Wave> _waves);
};
#endif
