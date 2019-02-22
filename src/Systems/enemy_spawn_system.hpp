#ifndef Enemy_Spawn_H
#define Enemy_Spawn_H

#include "entity_manager.hpp"
#include "EntityFactories/enemy_factory.hpp"

class EnemySpawnSystem {
  public:
    EnemySpawnSystem();
    ~EnemySpawnSystem();
    void spawnEnemy(EntityManager& entityManager);
    void reduceElapsedTime(EntityManager& entityManager, float dt);
  private:
    EnemyFactory factory;
    int enemyCount;
};

#endif
