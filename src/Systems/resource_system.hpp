#ifndef RESOURCE_SYSTEM_H
#define RESOURCE_SYSTEM_H

#include "utility.hpp"
#include "entity.hpp"
#include "entity_manager.hpp"
#include "Components/sprite_component.hpp"
#include "Components/transform_component.hpp"
#include "Components/movement_component.hpp"
#include "Components/resource_component.hpp"

class ResourceSystem 
{
public:
	void handleResourceSpawnAndDespawn(EntityManager &entityManager, float dt);
	void updateSpawn(EntityManager& entityManager);
	void updateDespawn(EntityManager& entityManager, float dt);
};

#endif


