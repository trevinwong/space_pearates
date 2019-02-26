#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include "hud.hpp"
#include "audio_loader.hpp"
#include "utility.hpp"
#include "entity.hpp"
#include "entity_manager.hpp"
#include "math.hpp"
#include "Components/movement_component.hpp"
#include "Components/collision_component.hpp"
#include "Components/transform_component.hpp"
#include "Components/player_component.hpp"
#include "Components/enemy_component.hpp"
#include "Components/resource_component.hpp"
#include "Components/enemy_spawn_component.hpp"
#include "Components/wallet_component.hpp"
#include "EntityFactories/resource_factory.hpp"
#include "Systems/waveset_system.hpp"

using EntityGrid = vector<vector<vector<shared_ptr<Entity>>>>;

class CollisionSystem
{
public:
  void setScreenInfo(vec2 screen);
  EntityGrid preprocessEntitiesIntoGrid(vector<shared_ptr<Entity>> entities);
  void checkCollisions(EntityManager &entityManager, WavesetSystem &wavesetSystem);
private:
  vec2 screen;
  float MIN_CELL_SIZE = 66.0f; //Player size
  void handleCollision(shared_ptr<Entity> e1, shared_ptr<Entity> e2, EntityManager &entityManager, WavesetSystem &wavesetSystem);
};

#endif


