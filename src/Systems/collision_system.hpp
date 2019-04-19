#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include "hud.hpp"
#include "Utility/audio_loader.hpp"
#include "Utility/utility.hpp"
#include "entity.hpp"
#include "entity_manager.hpp"
#include "Utility/math.hpp"
#include "Components/movement_component.hpp"
#include "Components/collision_component.hpp"
#include "Components/transform_component.hpp"
#include "Components/player_component.hpp"
#include "Components/enemy_component.hpp"
#include "Components/resource_component.hpp"
#include "Components/wallet_component.hpp"
#include "Components/spline_component.hpp"
#include "Components/death_component.hpp"
#include "Components/damage_component.hpp"
#include "Components/sprite_component.hpp"
#include "EntityFactories/resource_factory.hpp"
#include "Systems/waveset_system.hpp"

using EntityGrid = vector<vector<vector<shared_ptr<Entity>>>>;

class CollisionSystem
{
public:
  void setScreenInfo(vec2 screen);
  EntityGrid preprocessEntitiesIntoGrid(vector<shared_ptr<Entity>> entities);
	bool checkIfCellIndicesAreInBound(pair<int, int> cell, int num_cells_in_row, int num_cells_in_col);
	void checkCollisions(EntityManager &entityManager);
	void handleCollisionOfType(bitset<ComponentType::max_count> components1, bitset<ComponentType::max_count> components2, shared_ptr<Entity> e1, shared_ptr<Entity> e2, EntityManager &entityManager, void(*handleCollisionFn)(shared_ptr<Entity>, shared_ptr<Entity>, EntityManager&));
	static void handlePlayerResource(shared_ptr<Entity> player, shared_ptr<Entity> resource, EntityManager &entityManager);
  static void handlePlayerEnemy(shared_ptr<Entity> player, shared_ptr<Entity> enemy, EntityManager &entityManager);
	static void handleProjectileEnemy(shared_ptr<Entity> projectile, shared_ptr<Entity> enemy, EntityManager &entityManager);
private:
  vec2 screen;
  float MIN_CELL_SIZE = 66.0f; //Player size
  void handleCollision(shared_ptr<Entity> e1, shared_ptr<Entity> e2, EntityManager &entityManager);
};

#endif


