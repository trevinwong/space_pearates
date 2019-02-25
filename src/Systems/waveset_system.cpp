#include "waveset_system.hpp"

WavesetSystem::WavesetSystem()
{
	srand(time(NULL));
}

void WavesetSystem::handleBuildAndDefensePhase(EntityManager &entityManager, float dt)
{
	vector<shared_ptr<Entity>> entities = entityManager.getEntities(entityManager.getComponentChecker(vector<int>{ComponentType::waveset}));

	for (shared_ptr<Entity> e : entities) {
		WavesetComponent *waveset_manager = e->getComponent<WavesetComponent>();
		Waveset waveset = waveset_manager->waveset;
		Wave wave = waveset.waves[waveNo];
		
		if (phase == BuildPhase) {				
			buildTimer += dt;
			if (buildTimer > wave.buildPhaseTime) startDefensePhase(wave.totalEnemies);
		}

		if (phase == DefensePhase) {
			defenseTimer += dt;
			if (isWaveOver(wave)) {
				if (isWavesetOver(waveset)) {
					HUD::getInstance().you_win = true;
				} else {
					waveNo++;
					startBuildPhase();
				}	
			} else {
				if (timeToSpawnNextCluster(wave)) {
					spawnCluster(entityManager, wave.clusters[clusterNo]);
					clusterNo++;
				}	
			}
		}
	}	
}

void WavesetSystem::startBuildPhase()
{
	phase = BuildPhase;
	buildTimer = 0;
}

void WavesetSystem::startDefensePhase(int totalEnemies)
{
	phase = DefensePhase;
	defenseTimer = 0;
	clusterNo = 0;
	currentEnemies = totalEnemies;
}

bool WavesetSystem::timeToSpawnNextCluster(Wave wave)
{
	return clusterNo < wave.clusters.size() && defenseTimer > wave.spawnTimes[clusterNo];
}

bool WavesetSystem::isWaveOver(Wave wave)
{
	return clusterNo >= wave.clusters.size() && currentEnemies == 0;
}

bool WavesetSystem::isWavesetOver(Waveset waveset)
{
	return waveNo >= waveset.waves.size();
}

void WavesetSystem::spawnCluster(EntityManager &entityManager, Cluster cluster)
{
	vector<vec2> enemyData = cluster.enemyData;
	for (int i = 0; i < enemyData.size(); i++) {
		//TODO: Do stuff based on enemyData[i].x (Enemy type ID)
		for (int j = 0; j < enemyData[i].y; j++) {
			//TODO: Spawn the enemy at spawn points instead.
			int xLoc = (rand() % 11 + 1) * 100;
			int xOffset = j * 5; 
			entityManager.addEntity(EnemyFactory::build(vec2(xLoc + xOffset, 100), vec2(0.0f, 40.f)));
		}
	}	
}
