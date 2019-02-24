#include "enemy_spawn_factory.hpp"

Entity EnemySpawnFactory::build(float spawnRate)
{
  EnemySpawnComponent *spawn = new EnemySpawnComponent(spawnRate);
  Entity e;
  e.setComponent<EnemySpawnComponent>(spawn);
  return e;
}
