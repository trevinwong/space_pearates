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

void ResourceSystem::checkEnemyDeath(EntityManager& entityManager) {
    // TODO: CHANGE PLAYER COMPONENT TO ENEMY COMPONENT
    vector<shared_ptr<Entity>> enemies = entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::player}));
    
    if (enemies.size() == 0) return;

    for (shared_ptr<Entity> enemy : enemies) {
        // TODO: CHECK IF ENEMY HAS RECENTLY DIED AND CALL spawnResource WITH ENEMY POSN
    }
}
void ResourceSystem::spawnResource(glm::vec2 position){
    // SPAWN RESOURCE WHERE ENEMY HAS DIED
}
