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
#include "subscriber.hpp"

class ResourceSystem : public Subscriber
{
public:
	ResourceSystem();
	~ResourceSystem();
	void updateCountdown(EntityManager& entityManager, float dt); // Decrement countdown timer for all resources on screen
    void removeResource(EntityManager& entityManager, shared_ptr<Entity> resource);
    void checkEnemyDeath(EntityManager& entityManager); // check if any enemies have died
    void spawnResource(glm::vec2 position); // resources spawn at loc where an enemy has died
private:
};

#endif


