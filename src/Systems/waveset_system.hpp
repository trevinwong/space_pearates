#ifndef WAVESET_SYSTEM_H
#define WAVESET_SYSTEM_H

// TODO: Remove unneeded includes
#include "utility.hpp"
#include "entity.hpp"
#include "entity_manager.hpp"
#include "Utility/waveset_structs.hpp"
#include "Components/waveset_component.hpp"
#include "Components/map_component.hpp"
#include "entityFactories/enemy_factory.hpp"
#include <time.h>       /* time */ //Only for the purposes of spawning at random locations.

class WavesetSystem
{
public:
	WavesetSystem();
	~WavesetSystem();

	waveset WavesetSystem::readWavesetFile(std::string fileName);
	wave WavesetSystem::readWaveDataFile(std::string fileName);
	cluster WavesetSystem::readClusterDataFile(std::string fileName);

	void mainWavesetAction(EntityManager &entityManager, float dt);

	void tickMainTimer(float dt);
	bool checkBuildPhaseEnd(wave w);
	void spawnCluster(EntityManager &entityManager, WavesetComponent* wp);
	bool enemyPhaseEnd(WavesetComponent* wp);
	bool advanceToNextWave(WavesetComponent* wp);
	int  getMaxClusters(WavesetComponent* wp);
	void enemyPhaseAction(EntityManager &entityManager, WavesetComponent* wp, float dt);
	void startEnemyPhase();
	void resetMainTimer();


	int getMaxWaves(WavesetComponent* wp);
	int resetWaveEnemies(WavesetComponent* wp);
	bool allClustersSpawned(WavesetComponent* wp);
	bool allWavesDone(WavesetComponent* wp);

	EnemyFactory enFactory;

	int totalWaveEnemies = 0;
	int waveEnemiesRemaining = 0;

	int waveNo = 0;
	int clusterNo = 0;
	enum phaseStateType {
		buildPhase,
		enemyPhase
	};
	phaseStateType phaseState = buildPhase; //TODO: Turn this into an enum

	float mainTimer; // Should be same type as world's dt.

};

#endif