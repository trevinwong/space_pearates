#ifndef RESOURCE_SYSTEM_H
#define RESOURCE_SYSTEM_H

// TODO: Remove unneeded includes
#include "utility.hpp"
#include "texture.hpp"
#include "program.hpp"
#include "entity.hpp"
#include "entity_manager.hpp"
#include "Components/sprite_component.hpp"
#include "Components/transform_component.hpp"
#include "Components/movement_component.hpp"
#include "Components/resource_component.hpp"

class ResourceSystem 
{
public:
	ResourceSystem();
	~ResourceSystem();
	void updateCountdown(EntityManager& entityManager, float dt); // Decrement countdown timer for all resources on screen
    void removeResource(EntityManager& entityManager, shared_ptr<Entity> resource);
private:
};

#endif


