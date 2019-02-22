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
<<<<<<< HEAD:src/Enemies/enemy.hpp
  float speed;
  //maps to the indices of the tile map matrix
  glm::vec2 pos;
  std::vector<std::vector<int>> map;

=======
  std::vector<std::vector<char>> map;
>>>>>>> added basic movement:src/Systems/enemy_system.hpp
};

#endif
