#ifndef WAVE_PHASE_COMPONENT_H
#define WAVE_PHASE_COMPONENT_H

#include "utility.hpp"
#include "base_component.hpp"
#include "entityFactories/enemy_factory.hpp"

// For entities that control the phases and waves of the level.
class WavePhaseComponent : public BaseComponent
{
public:
	WavePhaseComponent();
	~WavePhaseComponent();
	//static const int typeID = ComponentType::wavePhase;
	//inline virtual int getTypeID() const { return typeID; };

	// Enemy factories here to determine the possible enemies that can spawn.
	// vector<BaseComponent> enemyFactories;
	
	int buildTime;
	vector<int> numEnemies; // Number of enemies in each wave.  Size of the vector should be the number of waves.

	bool loopWaves = false; // Whether or not to restart at the first wave if all waves have been completed.
	int waveNo = 0; // The current wave.  TODO: Either keep here or move to system.
};

#endif
