#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include "utility.hpp"
#include "entity.hpp"
#include "entity_manager.hpp"
#include "math.hpp"
#include "Components/movement_component.hpp"
#include "Components/collision_component.hpp"
#include "Components/transform_component.hpp"
#include "Components/player_component.hpp"
#include "Components/enemy_component.hpp"

using EntityGrid = vector<vector<vector<shared_ptr<Entity>>>>;

class CollisionSystem
{
public:
	void setScreenInfo(vec2 screen);
	EntityGrid preprocessEntitiesIntoGrid(vector<shared_ptr<Entity>> entities);
	void checkCollisions(EntityManager &entityManager);
	void handleCollision(shared_ptr<Entity> e1, shared_ptr<Entity> e2);
private:
	vec2 screen;
	int NUM_CELLS_IN_ROW = 10;
	int NUM_CELLS_IN_COLUMN = 10;
};

#endif


