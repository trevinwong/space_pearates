#ifndef ENEMY_SPAWN_COMPONENT_H
#define ENEMY_SPAWN_COMPONENT_H

#include "utility.hpp"
#include "base_component.hpp"

class EnemySpawnComponent : public BaseComponent
{
public:
  EnemySpawnComponent(float sr);
  ~EnemySpawnComponent();

  float timeToSpawn;
  float spawnRate;
  int count;
  static const int typeID = ComponentType::enemy_spawn;
  inline virtual int getTypeID() const { return typeID; };
};

#endif