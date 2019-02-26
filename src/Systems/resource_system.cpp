#include "resource_system.hpp"

void ResourceSystem::handleResourceSpawnAndDespawn(EntityManager& entityManager, float dt) {
	updateSpawn(entityManager);
	updateDespawn(entityManager, dt);
}

void ResourceSystem::updateSpawn(EntityManager& entityManager) {
	// TO-DO: Check for EnemyComponent and DeathComponent. Then spawn resources at their location.
}

void ResourceSystem::updateDespawn(EntityManager& entityManager, float dt) {
	vector<shared_ptr<Entity>> resources = entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::resource}));

	for (shared_ptr<Entity> resource : resources) {
		ResourceComponent *resourceComponent = resource->getComponent<ResourceComponent>();
		resourceComponent->timer.update(dt);

		if (resourceComponent->timer.getTimeLeft() <= 0) {
    	entityManager.removeEntity(resource);
		}
	}
}