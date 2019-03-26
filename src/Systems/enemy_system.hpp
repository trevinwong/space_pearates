#ifndef ENEMY_SYSTEM_H
#define ENEMY_SYSTEM_H

#include "entity_manager.hpp"
#include "EntityFactories/enemy_factory.hpp"
#include "tile_map_system.hpp"
#include "hud.hpp"
#include "waveset_system.hpp"
#include "Components/map_component.hpp"

class EnemySystem
{
public:
  void move(float dt, EntityManager& entities);
<<<<<<< HEAD
  void moveShell (float dt, EntityManager& entityManager);
  void setMap(EntityManager& entities);
  void moveRandom (float dt, EntityManager& entityManager);
=======
  bool setMap(EntityManager& entityManager);
>>>>>>> 668dbca440fcc5d34844174d43462c8d3638069f
private:
  vector<vector<char>> map;
  vector<shared_ptr<Entity>> tiles;
};

#endif
