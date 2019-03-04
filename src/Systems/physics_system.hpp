#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H

#include "utility.hpp"
#include "entity.hpp"
#include "subscriber.hpp"
#include "entity_manager.hpp"
#include "line.hpp"
#include "Components/projectile_component.hpp"
#include "Components/sprite_component.hpp"
#include "Components/transform_component.hpp"
#include "Components/collision_component.hpp"
#include "Components/movement_component.hpp"
#include "Components/tile_component.hpp"
#include "Components/player_component.hpp"
#include "Components/TowerComponents/water_tower_factor_component.hpp"
#include "Events/collision_event.hpp"

class PhysicsSystem
{
public:
	void setScreenInfo(vec2 info);
	void moveEntities(EntityManager &entityManager, float dt);
  void rotateEntities(EntityManager &entityManager, float dt);

private:
	float FRICTION = 10000.0f;
	float GRAVITY = 5000.0f;
	float getGravity(float dt);
	float getFriction(vec2 velocity, float dt);
  void adjustPositionAroundTiles(EntityManager &entityManager, shared_ptr<Entity> &e);
	void adjustPositionOntoScreen(EntityManager &entityManager, shared_ptr<Entity> &e);
	vec2 screenInfo;
};

#endif
