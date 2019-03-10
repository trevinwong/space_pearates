#ifndef WAVESET_SYSTEM_H
#define WAVESET_SYSTEM_H

#include "utility.hpp"
#include "entity.hpp"
#include "entity_manager.hpp"
#include "Utility/waveset_structs.hpp"
#include "Components/waveset_component.hpp"
#include "Components/map_component.hpp"
#include "EntityFactories/enemy_factory.hpp"
#include "hud.hpp"
#include <time.h> 

class WavesetSystem
{
public:
  WavesetSystem(WavesetSystem const&) = delete;
  void operator=(WavesetSystem const&) = delete;
  static WavesetSystem& getInstance()
  {
    static WavesetSystem instance;
    return instance;
  }

  void reset();
	void handleBuildAndDefensePhase(EntityManager &entityManager, float dt);
	void startBuildPhase();
	void startDefensePhase(Wave &wave);
	bool timeToSpawnNextCluster(Wave &wave);
	bool isWaveOver(Wave &wave);
	bool isWavesetOver(Waveset &waveset);
	void spawnCluster(EntityManager &entityManager, Cluster cluster);
	void decrementEnemies(int amount, EntityManager &entityManager);

	int waveNo = 0;
	int clusterNo = 0;

	enum PhaseType {
		BuildPhase,
		DefensePhase
	};

	PhaseType phase = BuildPhase; 
	float buildTimer;
	float defenseTimer;
	vector<glm::vec2> enemySpawnPoints;
private:
	WavesetSystem();
};

#endif
