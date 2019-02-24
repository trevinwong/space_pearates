#ifndef Enemy_Spawn_H
#define Enemy_Spawn_H

#include "entity_manager.hpp"
#include "EntityFactories/enemy_factory.hpp"

class EnemySpawnSystem {
public:
	void spawnEnemy(EntityManager& entityManager);
	void reduceElapsedTime(EntityManager& entityManager, float dt);
private:
	int enemyCount;
};

#endif
