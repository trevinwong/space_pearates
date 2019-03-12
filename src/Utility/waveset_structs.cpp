#include "waveset_structs.hpp"

Cluster::Cluster(vector<vec2> _enemyData) :
	enemyData(_enemyData)
{
}

Wave::Wave(int _buildPhaseTime, vector<int> _spawnTimes, vector<Cluster> _clusters) :
	buildPhaseTime(_buildPhaseTime), spawnTimes(_spawnTimes), clusters(_clusters)
{
	for (Cluster cluster : clusters) {
		vector<vec2> enemyData = cluster.enemyData;
		for (vec2 ed : enemyData) totalEnemies += ed.y;
	}
}

Waveset::Waveset(vector<Wave> _waves, vector<int> _hpMult, vector<int> _spdMult, vector<int> _atkMult) :
	waves(_waves), hpMult(_hpMult), spdMult(_spdMult), atkMult(_atkMult)
{
}
