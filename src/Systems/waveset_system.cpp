#include "waveset_system.hpp"

WavesetSystem::WavesetSystem()
{
	mainTimer = 0;
	srand(time(NULL));
}

WavesetSystem::~WavesetSystem()
{

}

//Main update() action for the waveset system
void WavesetSystem::mainWavesetAction(EntityManager &entityManager, float dt)
{
	vector<shared_ptr<Entity>> entities = entityManager.getEntities(entityManager.getComponentChecker(vector<int>{ComponentType::waveset}));
	for (shared_ptr<Entity> e : entities) {
		WavesetComponent *wp_component = e->getComponent<WavesetComponent>();

		
		if (wp_component != nullptr)
		{
			if (totalWaveEnemies == 0) //For first wave
			{
				resetWaveEnemies(wp_component);
			}
			tickMainTimer(dt);
			if (phaseState == buildPhase)
			{
				//Currently Build Phase
				if (!allWavesDone(wp_component)) //Safeguard
				{
					checkBuildPhaseEnd(wp_component->m_waveset.waves[waveNo]);
				}
				
			}
			else
			{
				//Currently Enemy Phase
				enemyPhaseAction(entityManager, wp_component, dt);
			}
		}


	}
	
	
}
// Get the maximum number of clusters in the current wave.
int WavesetSystem::getMaxClusters(WavesetComponent* wp)
{
	waveset waveset = wp->m_waveset;
	wave currentWave = waveset.waves[waveNo];
	return currentWave.clusters.size();
}

//Get the maximum number of waves in the waveset.
int WavesetSystem::getMaxWaves(WavesetComponent* wp)
{
	waveset waveset = wp->m_waveset;
	return waveset.waves.size();
}

//Recalculates information regarding the number of enemies in the wave.
int WavesetSystem::resetWaveEnemies(WavesetComponent* wp)
{
	//Calculate the wave enemies:
	waveset waveset = wp->m_waveset;
	wave currentWave = waveset.waves[waveNo];
	int total = 0;
	//Iterate through all clusters
	for (int k = 0; k < currentWave.clusters.size(); k++)
	{
		cluster nextCluster = currentWave.clusters[k];
		std::vector<glm::vec2> enemyData = nextCluster.enemyData;
		//Add for every enemy in the cluster.
		for (int i = 0; i < enemyData.size(); i++)
		{
			total += enemyData[i].y;
		}
	}
	totalWaveEnemies = total;
	waveEnemiesRemaining = total;
	return total;
}

// Main enemy phase code
void WavesetSystem::enemyPhaseAction(EntityManager &entityManager, WavesetComponent* wp, float dt)
{
	waveset waveset = wp->m_waveset;
	wave currentWave = waveset.waves[waveNo];
	int nextSpawnTime = 99999999;
	//To avoid invalid array access.
	if (!allClustersSpawned(wp))
	{
		nextSpawnTime = currentWave.spawnTimes[clusterNo];
	}
	//If there are still clusters to be spawned...
	if (clusterNo < getMaxClusters(wp))
	{
		//Check if ready to spawn next cluster.
		if (mainTimer > nextSpawnTime)
		{
			//Safeguard
			if (!allClustersSpawned(wp))
			{
				spawnCluster(entityManager, wp);
			}
			
		}
	}
	else
	{
		//Check if ready to advance to the next wave.
		if (enemyPhaseEnd(wp))
		{
			advanceToNextWave(wp);
		}
		
	}
	
}

// Returns true if there are still more waves to go.
bool WavesetSystem::advanceToNextWave(WavesetComponent* wp)
{
	clusterNo = 0;
	phaseState = buildPhase;
	waveNo++;
	if (!allWavesDone(wp))
	{
		resetWaveEnemies(wp);
		return true;
	}
	else
	{
		//TODO: Temp: Loops back to first wave.
		resetWaveEnemies(wp);
		waveNo = 0;
		return false;
	}
}

//Spawns the current cluster.
void WavesetSystem::spawnCluster(EntityManager &entityManager, WavesetComponent* wp)
{
	waveset waveset = wp->m_waveset;
	wave currentWave = waveset.waves[waveNo];
	cluster nextCluster = currentWave.clusters[clusterNo];
	int nextSpawnTime = currentWave.spawnTimes[clusterNo];

	//Spawn based on waveNo and clusterNo.
	std::vector<glm::vec2> enemyData = nextCluster.enemyData;
	for (int i = 0; i < enemyData.size(); i++)
	{
		//TODO: Do stuff based on enemyData[i].x (Enemy type ID)
		for (int j = 0; j < enemyData[i].y; j++)
		{
			//TODO: Spawn the enemy at spawn points instead.
			int xLoc = (rand() % 11 + 1) * 100;
			int xOffset = j * 5; //So that enemies in the same cluster won't overlap.
			Entity enemy = EnemyFactory::build(glm::vec2(xLoc + xOffset, 100), glm::vec2(16, 16), glm::vec2(0.f, 40.f));
			entityManager.addEntity(enemy);
		}
	}
	
	//Advance to next cluster.
	clusterNo++;
	
}

//Reset timer; call this when switching phases.
void WavesetSystem::resetMainTimer()
{
	mainTimer = 0;
}

//Should be in the world update call stack.
void WavesetSystem::tickMainTimer(float dt)
{
	mainTimer += dt;
}

//Call this when enemy phase begins
void WavesetSystem::startEnemyPhase()
{
	phaseState = enemyPhase;
	clusterNo = 0;
	resetMainTimer();
}

// Check if build phase has ended.
bool WavesetSystem::checkBuildPhaseEnd(wave w)
{
	if (mainTimer >= w.buildPhaseTime)
	{
		startEnemyPhase();
		return true;
	}
	else
	{
		return false;
	}
	
}

//Checks if all clusters in the current wave have spawned.
bool WavesetSystem::allWavesDone(WavesetComponent* wp)
{
	if (waveNo >= getMaxWaves(wp))
	{
		return true;
	}
	return false;
}

//Checks if all clusters in the current wave have spawned.
bool WavesetSystem::allClustersSpawned(WavesetComponent* wp)
{
	if (clusterNo >= getMaxClusters(wp))
	{
		return true;
	}
	return false;
}

//Check if ready to advance to the next wave.
bool WavesetSystem::enemyPhaseEnd(WavesetComponent* wp)
{
	if (allClustersSpawned(wp) )
	{
		// Check the amount of enemies remaining in the current wave.
		if (waveEnemiesRemaining == 0) //Disable this check if want to debug with no enemy destruction.
		{
			return true;
		}
		
	}
	return false;
}