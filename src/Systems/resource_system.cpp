#include "resource_system.hpp"

ResourceSystem::ResourceSystem()
{
}

ResourceSystem::~ResourceSystem()
{
}


// Perform movement on all entities with the movement component.
void ResourceSystem::updateCountdown(EntityManager& entityManager, float dt) {
      vector<shared_ptr<Entity>> resources = entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::resource}));

      if (resources.size() == 0) return; // No resources on screen, nothing to update

	for (shared_ptr<Entity> resource : resources) {
        SpriteComponent *spriteComponent = resource->getComponent<SpriteComponent>();
        TransformComponent *transformComponent = resource->getComponent<TransformComponent>();
        ResourceComponent *resourceComponent = resource->getComponent<ResourceComponent>();
		if (resourceComponent == nullptr || spriteComponent == nullptr || transformComponent == nullptr) {
            continue;
        }
        
        resourceComponent->updateTimer(dt);
        if (resourceComponent->checkTimer() <= 0) { // No more time left for resource
            removeResource(entityManager, resource);
        }
    }
}

void ResourceSystem::removeResource(EntityManager& entityManager, shared_ptr<Entity> resource) {
    entityManager.removeEntity(resource);
}
