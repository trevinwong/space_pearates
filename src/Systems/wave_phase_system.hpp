#ifndef WAVE_PHASE_SYSTEM_H
#define WAVE_PHASE_SYSTEM_H

// TODO: Remove unneeded includes
#include "utility.hpp"
#include "texture.hpp"
#include "program.hpp"
#include "entity.hpp"
#include "Components/wave_phase_component.hpp"
#include "entityFactories/enemy_factory.hpp"

class WavePhaseSystem
{
public:
	WavePhaseSystem();
	~WavePhaseSystem();

	struct cluster {
		std::vector<glm::vec2> enemyData; //x is the enemy ID while y is the enemy amount.
	};

	struct wave {
		int buildPhaseTime;
		std::vector<int> spawnTimes;
		std::vector<cluster> clusters;
	};

	wave WavePhaseSystem::readWaveDataFile(std::string fileName);
	cluster WavePhaseSystem::readClusterDataFile(std::string fileName);

	void mainStateLoop(float dt);

	void tickMainTimer(float dt);
	bool checkBuildPhaseEnd();

	int checkRemainingEnemies();

	void enemyPhaseAction();

	void resetMainTimer();
	void resetBPTimer();

	void interpSubwaveFile();

	int waveNo = 0;
	int phaseState = 0; //TODO: Turn this into an enum

	float mainTimer; // Should be same type as world's dt.
	float buildPhaseEndTime;
	float enemyPhaseStartTime;
	double timerPos;
	double waveNoPos;
	double enemyRemainingPos;

	//MapComponent mapComponent;



};

#endif