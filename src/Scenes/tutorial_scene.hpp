#ifndef TUTORIAL_SCENE_H
#define TUTORIAL_SCENE_H

#include "Utility/utility.hpp"
#include "Scenes/abstract_scene.hpp"
#include "DataLoaders/tower_data_loader.hpp"
#include "DataLoaders/player_data_loader.hpp"
#include "Scenes/scene_manager.hpp"
#include "help_menu.hpp"

#include "EntityFactories/background_entity_factory.hpp"
#include "EntityFactories/map_entity_factory.hpp"
#include "EntityFactories/player_factory.hpp"
#include "EntityFactories/resource_factory.hpp"
#include "EntityFactories/tower_ui_entity_factory.hpp"
#include "EntityFactories/enemy_factory.hpp"
#include "EntityFactories/simple_sprite_factory.hpp"

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

namespace TutorialStep {
  enum TutorialStep {
    prologue,
    hud_tutorial,
    introduce_elements,
    try_to_move_and_pick_up_coins,
    learned_move_done,
    an_enemy_is_coming,
    show_enemy_target,
    try_to_build_a_tower,
    the_enemy_is_moving,
    the_enemy_is_killed,
    tutorial_done
  };
}


class TutorialScene : public AbstractScene
{
public:
  TutorialScene(std::weak_ptr<SceneManager> _sceneManager);
  ~TutorialScene();
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

  bool paused = false;

  TutorialStep::TutorialStep currentStep;

  shared_ptr<Entity> tutorialIndicator; // display tutorial images
  shared_ptr<Entity> sampleEnemy;

  void tutorialInputProcess(float dt, GLboolean keys[], GLboolean keysProcessed[]);
  void tutorialUpdate(float dt);

};

#endif // !TUTORIAL_SCENE_H
