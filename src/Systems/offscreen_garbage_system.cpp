#include "offscreen_garbage_system.hpp"

void OffscreenGarbageSystem::destroyEntitiesContaining(EntityManager & entityManager, ComponentType::ComponentType type)
{
  destroyEntitiesContaining(entityManager, vector<int>{type});
}

void OffscreenGarbageSystem::destroyEntitiesContaining(EntityManager & entityManager, vector<int> component_types)
{
  vector<shared_ptr<Entity>> targetEntities = entityManager.getEntitiesHasOneOf(entityManager.getComponentChecker(component_types));
  destroyOffscreen(entityManager, targetEntities);
}

void OffscreenGarbageSystem::destroyEntitiesContainingAll(EntityManager & entityManager, vector<int> component_types)
{
  vector<shared_ptr<Entity>> targetEntities = entityManager.getEntitiesHasAllOf(entityManager.getComponentChecker(component_types));
  destroyOffscreen(entityManager, targetEntities);
}

void OffscreenGarbageSystem::destroyOffscreen(EntityManager & entityManager, vector<shared_ptr<Entity>> entities)
{
  for (shared_ptr<Entity> targetEntity : entities) {
    shared_ptr<TransformComponent> transformComponent = targetEntity->getComponent<TransformComponent>();
    shared_ptr<SplineComponent> splineComponent = targetEntity->getComponent<SplineComponent>();
    if (splineComponent != nullptr) continue;
    if (transformComponent == nullptr) continue;

    auto leftTopPositon = transformComponent->position;
    auto size = transformComponent->size;

    if ((leftTopPositon.x > SCREEN_WIDTH || leftTopPositon.x + size.x < 0.0) ||
      (leftTopPositon.y > SCREEN_HEIGHT || leftTopPositon.y + size.y < 0.0))
    {
      entityManager.removeEntity(targetEntity);
    }
  }
}
