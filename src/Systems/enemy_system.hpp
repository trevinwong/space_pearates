#ifndef ENEMY_SYSTEM_H
#define ENEMY_SYSTEM_H

#include "entity_manager.hpp"
#include "EntityFactories/enemy_factory.hpp"
#include "tile_map_system.hpp"
#include "hud.hpp"
#include "waveset_system.hpp"

class EnemySystem
{
public:
  void move(float dt, EntityManager& entities, WavesetSystem &wavesetSystem);
  void getMap(EntityManager& entities);
private:
  std::vector<std::vector<char>> map;
};

#endif
