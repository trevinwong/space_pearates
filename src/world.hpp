#ifndef WORLD_H
#define WORLD_H

#include "Utility/utility.hpp"
#include "Scenes/abstract_scene.hpp"
#include "hud.hpp"
#include "help_menu.hpp"
#include "game_over_menu.hpp"
#include "Scenes/scene_manager.hpp"
#include "Systems/enemy_system.hpp"
#include "Utility/waveset_structs.hpp"
#include "entity_manager.hpp"
#include "Systems/tile_map_system.hpp"
#include "Systems/sprite_system.hpp"
#include "Systems/physics_system.hpp"
#include "Systems/interpolation_system.hpp"
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
#include "Systems/damage_system.hpp"
#include "Systems/home_system.hpp"
#include "Systems/mesh_system.hpp"
#include "Systems/state_system.hpp"
#include "EntityFactories/map_entity_factory.hpp"
#include "EntityFactories/background_entity_factory.hpp"
#include "EntityFactories/player_factory.hpp"
#include "EntityFactories/resource_factory.hpp"
#include "EntityFactories/tower_ui_entity_factory.hpp"
#include "EntityFactories/waveset_manager_factory.hpp"
#include "Components/collision_component.hpp"
#include "Components/transform_component.hpp"
#include "DataLoaders/tower_data_loader.hpp"
#include "DataLoaders/player_data_loader.hpp"

// TO-DO: Look into replacing Keys array with direct callback.
// TO-DO: Look into replacing processInput with direct callback.
// TO-DO: Look into not having to include every component file.
class World : public AbstractScene
{
public:
  World(std::weak_ptr<SceneManager> _sceneManager, int _level);
  ~World();
  void reset();
  void processInput(float dt, GLboolean keys[], GLboolean keysProcessed[]);
  void update(float dt); // dt = delta time, how much time has passed since update was last called
  void draw();

private:
  PhysicsSystem physicsSystem;
  InterpolationSystem interpolationSystem;
  CollisionSystem collisionSystem;

  SpriteSystem spriteSystem;
  BackgroundSystem backgroundSystem;
  BillboardSystem billboardSystem;

  EnemySystem enemySystem;
  PlayerSystem playerSystem;
	MeshSystem meshSystem;
  StateSystem stateSystem;

  TowerRangeDisplaySystem towerRangeDisplaySystem;
  TowerAttackSystem towerAttackSystem;
  TowerUiSystem towerUiSystem;
  RenderToTextureSystem renderToTextureSystem;

  OffscreenGarbageSystem offscreenGarbageSystem;
  ParticleSystem particleSystem;
  ResourceSystem resourceSystem;
	DamageSystem damageSystem;
	DeathSystem deathSystem;
  HomeSystem homeSystem;

  int level;
  bool hasWon = false;
  bool paused = false;
  vec2 player_spawn = vec2(0.0f, 0.0f);
  shared_ptr<Entity> player;
  shared_ptr<Entity> home;
  shared_ptr<Entity> map;
};

#endif
