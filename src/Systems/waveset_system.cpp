#include "waveset_system.hpp"

WavesetSystem::WavesetSystem()
{
	srand(time(NULL));
}

void WavesetSystem::reset()
{
  waveNo = 0;
  clusterNo = 0;
  phase = BuildPhase;
  buildTimer = 0;
  defenseTimer = 0;
}

bool WavesetSystem::handleBuildAndDefensePhase(EntityManager &entityManager, float dt)
{
	vector<shared_ptr<Entity>> entities = entityManager.getEntities(entityManager.getComponentChecker(vector<int>{ComponentType::waveset}));

	for (shared_ptr<Entity> e : entities) {
		shared_ptr<WavesetComponent> waveset_manager = e->getComponent<WavesetComponent>();
		Waveset &waveset = waveset_manager->waveset;

		if (isWavesetOver(waveset)) {
      return true;
		}

		Wave &wave = waveset.waves[waveNo];
		int hp = waveset.hpMult[waveNo];
		int spd = waveset.spdMult[waveNo];
		int atk = waveset.atkMult[waveNo];

		if (phase == BuildPhase) {
			buildTimer += dt;
			HUD::getInstance().build_phase = true;
			if (buildTimer > wave.buildPhaseTime) startDefensePhase(wave);
		}

		if (phase == DefensePhase) {
			defenseTimer += dt;
			HUD::getInstance().build_phase = false;
			HUD::getInstance().enemy_count = wave.currEnemies;
			if (isWaveOver(wave)) {
				waveNo++;
				startBuildPhase();
			} else {
				if (timeToSpawnNextCluster(wave)) {
					spawnCluster(entityManager, wave.clusters[clusterNo], hp, spd, atk);
					clusterNo++;
				}
			}
		}
	}
  return false;
}

void WavesetSystem::startBuildPhase()
{
	phase = BuildPhase;
	buildTimer = 0;
}

void WavesetSystem::startDefensePhase(Wave &wave)
{
	phase = DefensePhase;
	defenseTimer = 0;
	clusterNo = 0;
	wave.currEnemies = wave.totalEnemies;
}

bool WavesetSystem::timeToSpawnNextCluster(Wave &wave)
{
	return clusterNo < wave.clusters.size() && defenseTimer > wave.spawnTimes[clusterNo];
}

bool WavesetSystem::isWaveOver(Wave &wave)
{
	return clusterNo >= wave.clusters.size() && wave.currEnemies <= 0;
}

bool WavesetSystem::isWavesetOver(Waveset &waveset)
{
	return waveNo >= waveset.waves.size();
}

void WavesetSystem::spawnCluster(EntityManager &entityManager, Cluster cluster,
	int hp, int spd, int atk)
{
	vector<vec2> enemyData = cluster.enemyData;
	for (int i = 0; i < enemyData.size(); i++) {
		//TODO: Do stuff based on enemyData[i].x (Enemy type ID)
		for (int j = 0; j < enemyData[i].y; j++) {
			//TODO: Spawn the enemy at spawn points instead.
			if (enemySpawnPoints.size() == 0)
			{
				//Failsafe in case spawnpoints were not found.
				int xLoc = (rand() % 11 + 1) * 100;
				int xOffset = j * 5;
				entityManager.addEntity(EnemyFactory::build(vec2(xLoc + xOffset, 100), vec2(0.0f, 40.f),
					hp, spd, atk, enemyData[i].x));
			}
			else
			{
				int spawnPointIndex = (rand() % enemySpawnPoints.size());
				glm::vec2 spawnPoint = enemySpawnPoints[spawnPointIndex];
				entityManager.addEntity(EnemyFactory::build(spawnPoint, vec2(0.0f, 40.f),
					hp, spd, atk, enemyData[i].x));
			}
		}
	}
}

// Refactor this and refactor the waveset data out of a component and into a class.
void WavesetSystem::decrementEnemies(int amount, EntityManager &entityManager)
{
	vector<shared_ptr<Entity>> entities = entityManager.getEntities(entityManager.getComponentChecker(vector<int>{ComponentType::waveset}));

	for (shared_ptr<Entity> e : entities) {
		shared_ptr<WavesetComponent> waveset_manager = e->getComponent<WavesetComponent>();
		Waveset &waveset = waveset_manager->waveset;
		if (!isWavesetOver(waveset)) {
			Wave &wave = waveset.waves[waveNo];
			wave.currEnemies -= amount;
		}
	}
}
