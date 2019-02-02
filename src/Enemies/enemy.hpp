#ifndef Enemy_H
#define Enemy_H

#include "entity_manager.hpp"
#include "enemy_factory.hpp"
#include "../TileMapping/tile_map_system.hpp"

class Enemy
{
public:
  Enemy();
  ~Enemy();
  void loadEnemy(glm::vec2 screen, EntityManager& entities);
  void move();
private:
  EnemyFactory factory;
};

#endif