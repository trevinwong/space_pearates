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
				healBase(entityManager, 30);
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

void WavesetSystem::healBase(EntityManager &entityManager, int healAmount)
{
	bool wasHealed = false;
	vector<shared_ptr<Entity>> homeEntities = entityManager.getEntities(entityManager.getComponentChecker(vector<int>{ComponentType::home}));
	for (shared_ptr<Entity> h : homeEntities) {
		shared_ptr<HealthComponent> health = h->getComponent<HealthComponent>();
		shared_ptr<TransformComponent> transform = h->getComponent<TransformComponent>();
		if (health->curHP != health->maxHP)
		{
			health->curHP += healAmount;
			ParticleSystem::emitSparkle(entityManager, glm::vec2(transform->position.x + (BASE_WIDTH / 2) + 25, transform->position.y));
			wasHealed = true;
		}
		
	}
	vector<shared_ptr<Entity>> playerEntities = entityManager.getEntities(entityManager.getComponentChecker(vector<int>{ComponentType::player}));
	for (shared_ptr<Entity> p : playerEntities) {
		shared_ptr<HealthComponent> health = p->getComponent<HealthComponent>();
		shared_ptr<TransformComponent> transform = p->getComponent<TransformComponent>();
		if (health->curHP != health->maxHP)
		{
			health->curHP += 1;
			ParticleSystem::emitSparkle(entityManager, glm::vec2(transform->position.x + 18, transform->position.y));
			wasHealed = true;
		}
	}
	if (wasHealed)
	{
		Mix_PlayChannel(-1, AudioLoader::getInstance().heal, 0);
	}
	
}

void WavesetSystem::startBuildPhase()
{
	phase = BuildPhase;
	buildTimer = 0;
}

void WavesetSystem::startDefensePhase(Wave &wave)
{
	Mix_PlayChannel(-1, AudioLoader::getInstance().defense_phase, 0);
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
					hp, spd, atk));
			}
			else
			{
				int spawnPointIndex = (rand() % enemySpawnPoints.size());
				glm::vec2 spawnPoint = enemySpawnPoints[spawnPointIndex];
				entityManager.addEntity(EnemyFactory::build(spawnPoint, vec2(0.0f, 40.f),
					hp, spd, atk));
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
