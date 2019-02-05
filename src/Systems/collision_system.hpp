#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

// TODO: Remove unneeded includes
#include "utility.hpp"
#include "texture.hpp"
#include "program.hpp"
#include "entity.hpp"
#include "Components/sprite_component.hpp"
#include "Components/transform_component.hpp"
#include "Components/movement_component.hpp"
#include "Components/collision_component.hpp"

class CollisionSystem
{
public:
	CollisionSystem();
	~CollisionSystem();

	void checkCollisions(std::vector<Entity> &entities);

private:
  bool isCollision(Entity &one, Entity &two);
};

#endif


