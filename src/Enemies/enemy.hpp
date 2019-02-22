#ifndef Enemy_H
#define Enemy_H

#include "entity_manager.hpp"
#include "EntityFactories/enemy_factory.hpp"
#include "../Systems/tile_map_system.hpp"

class Enemy
{
public:
  Enemy();
  ~Enemy();
  void loadEnemy(glm::vec2 screen, EntityManager& entities);
  void move(float dt);
  void getMap(EntityManager& entities);
private:
  EnemyFactory factory;
  float speed;
  //maps to the indices of the tile map matrix
  glm::vec2 pos;
  std::vector<std::vector<char>> map;

};

#endif
