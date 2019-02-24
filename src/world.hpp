#ifndef WORLD_H
#define WORLD_H

#include "utility.hpp"
#include "hud.hpp"
#include "Systems/enemy_system.hpp"
#include "Systems/enemy_spawn_system.hpp"
#include "entity_manager.hpp"
#include "Systems/tile_map_system.hpp"
#include "Systems/event_system.hpp"
#include "Systems/sprite_system.hpp"
#include "Systems/physics_system.hpp"
#include "Systems/billboard_system.hpp"
#include "Systems/player_system.hpp"
#include "Systems/resource_system.hpp"
#include "Systems/collision_system.hpp"
#include "Systems/tower_ui_system.hpp"
#include "Systems/tower_range_display_system.hpp"
#include "Systems/tower_attack_system.hpp"
#include "Systems/offscreen_garbage_system.hpp"
#include "EntityFactories/map_entity_factory.hpp"
#include "EntityFactories/player_factory.hpp"
#include "EntityFactories/resource_factory.hpp"
#include "EntityFactories/enemy_spawn_factory.hpp"
#include "EntityFactories/tower_ui_entity_factory.hpp"

// TO-DO: Look into replacing Keys array with direct callback.
// TO-DO: Look into replacing processInput with direct callback.
// TO-DO: Look into not having to include every component file.
class World
{
public:
  World();
  ~World();
  void init(glm::vec2 screen);
  void update(float dt); // dt = delta time, how much time has passed since update was last called
  void processInput(float dt);
  void draw();
  void destroy();
  GLboolean keys[1024];
  GLboolean keysProcessed[1024];

private:
  HUD hud;
  EntityManager entityManager;
  EventSystem eventSystem;
  SpriteSystem spriteSystem;
  BillboardSystem billboardSystem;
  glm::mat4 projection;
  TileMapSystem tileMapSystem;
  //Change later after figuring out how to read multiple enemies
  EnemySystem enemySystem;
  EnemySpawnSystem enemySpawnSystem;
  PlayerSystem playerSystem;
	PhysicsSystem physicsSystem;
  CollisionSystem collisionSystem;
  TowerRangeDisplaySystem towerRangeDisplaySystem;
  TowerAttackSystem towerAttackSystem;
  OffscreenGarbageSystem projectileGarbageSystem;
  ResourceSystem resourceSystem;
  TowerUiSystem towerUiSystem;
};

#endif
