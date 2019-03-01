#ifndef WORLD_H
#define WORLD_H

#include "utility.hpp"
#include "hud.hpp"
#include "Systems/enemy_system.hpp"
#include "Systems/enemy_spawn_system.hpp"
#include "Utility/waveset_structs.hpp"
#include "entity_manager.hpp"
#include "Systems/tile_map_system.hpp"
#include "Systems/event_system.hpp"
#include "Systems/sprite_system.hpp"
#include "Systems/physics_system.hpp"
#include "Systems/billboard_system.hpp"
#include "Systems/enemy_system.hpp"
#include "Systems/player_system.hpp"
#include "Systems/resource_system.hpp"
#include "Systems/collision_system.hpp"
#include "Systems/tower_ui_system.hpp"
#include "Systems/tower_range_display_system.hpp"
#include "Systems/tower_attack_system.hpp"
#include "Systems/offscreen_garbage_system.hpp"
#include "Systems/render_to_texture_system.hpp"
#include "Systems/background_system.hpp"
#include "Systems/waveset_system.hpp"
#include "Systems/death_system.hpp"
#include "Systems/particle_system.hpp"
#include "EntityFactories/map_entity_factory.hpp"
#include "EntityFactories/background_entity_factory.hpp"
#include "EntityFactories/player_factory.hpp"
#include "EntityFactories/resource_factory.hpp"
#include "EntityFactories/enemy_spawn_factory.hpp"
#include "EntityFactories/tower_ui_entity_factory.hpp"
#include "EntityFactories/waveset_manager_factory.hpp"
#include "Components/collision_component.hpp"
#include "Components/transform_component.hpp"

// TO-DO: Look into replacing Keys array with direct callback.
// TO-DO: Look into replacing processInput with direct callback.
// TO-DO: Look into not having to include every component file.
class World
{
public:
  void init(vec2 screen);
  void processInput(float dt, GLboolean keys[], GLboolean keysProcessed[]);
  void update(float dt); // dt = delta time, how much time has passed since update was last called
  void draw();
  void destroy();
  vec2 player_spawn = vec2(0.0f, 0.0f);

private:
  glm::mat4 projection;
  EntityManager entityManager;
  PhysicsSystem physicsSystem;
  CollisionSystem collisionSystem;
	DeathSystem deathSystem;
  SpriteSystem spriteSystem;
  BackgroundSystem backgroundSystem;
  BillboardSystem billboardSystem;
  EnemySystem enemySystem;
  PlayerSystem playerSystem;
  ResourceSystem resourceSystem;

  TowerRangeDisplaySystem towerRangeDisplaySystem;
  TowerAttackSystem towerAttackSystem;
  TowerUiSystem towerUiSystem;

  WavesetSystem wavesetSystem;
  OffscreenGarbageSystem offscreenGarbageSystem;
  ParticleSystem particleSystem;
  RenderToTextureSystem renderToTextureSystem;
};

#endif
