#ifndef Enemy_H
#define Enemy_H

#include "entity_manager.hpp"
#include "EntityFactories/enemy_factory.hpp"
#include "tile_map_system.hpp"

class Enemy
{
public:
  Enemy();
  ~Enemy();
  void loadEnemy(vec2 screen, EntityManager& entities);
  void move(float dt, EntityManager& entities);
  void getMap(EntityManager& entities);
private:
  EnemyFactory factory;
  std::vector<std::vector<char>> map;
};

#endif
