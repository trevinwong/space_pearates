#include "enemy_spawn_system.hpp"

void EnemySpawnSystem::spawnEnemy(EntityManager& entityManager) {

  vector<shared_ptr<Entity>> spawnEntities =
    entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::enemy_spawn}));

  for (shared_ptr<Entity> spawnEntity : spawnEntities) {
    EnemySpawnComponent *sc = spawnEntity->getComponent<EnemySpawnComponent>();
    if (sc->timeToSpawn <= 0) {
      entityManager.addEntity(EnemyFactory::build(vec2(600, 5), vec2(0.f, 40.f)));
      sc->timeToSpawn = sc->spawnRate;
      sc->count++;
    }
  }
}

void EnemySpawnSystem::reduceElapsedTime(EntityManager& entityManager, float dt) {
  vector<shared_ptr<Entity>> spawnEntities =
    entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::enemy_spawn}));

  for (shared_ptr<Entity> spawnEntity : spawnEntities) {
    EnemySpawnComponent *sc = spawnEntity->getComponent<EnemySpawnComponent>();
    if (sc)
      sc->timeToSpawn -= dt;
  }
}
