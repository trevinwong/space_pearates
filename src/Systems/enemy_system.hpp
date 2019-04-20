#ifndef ENEMY_SYSTEM_H
#define ENEMY_SYSTEM_H

#include "entity_manager.hpp"
#include "EntityFactories/enemy_factory.hpp"
#include "tile_map_system.hpp"
#include "hud.hpp"
#include "waveset_system.hpp"
#include "Components/map_component.hpp"
#include "Components/enemy_path_component.hpp"
#include "Utility/audio_loader.hpp"


class EnemySystem
{
public:
  bool setMap(EntityManager& entityManager);
  void move(float dt, EntityManager& entities);
  void moveShell(float dt, EntityManager& entityManager, shared_ptr<Entity> home, shared_ptr<Entity> e);
  void moveBasic(float dt, EntityManager& entityManager, shared_ptr<Entity> home, shared_ptr<Entity> e);
  void moveAstar(float dt, EntityManager& entityManager, shared_ptr<Entity> home, shared_ptr<Entity> e);
  void moveGhost(float dt, EntityManager& entityManager, shared_ptr<Entity> home, shared_ptr<Entity> e);

private:
  vector<vector<char>> map;
  int TILE_SIZE_X;
  int TILE_SIZE_Y;
  int MAP_WIDTH;
  int MAP_HEIGHT;
};

#endif
