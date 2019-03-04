#include "offscreen_garbage_system.hpp"

void OffscreenGarbageSystem::destroyOffScreenEntities(EntityManager & entityManager, ComponentType::ComponentType type)
{
  checkAndDestroy(entityManager, vector<int>{type});
}

void OffscreenGarbageSystem::destroyOffScreenEntities(EntityManager & entityManager, vector<int> component_types)
{
  checkAndDestroy(entityManager, component_types);
}

void OffscreenGarbageSystem::checkAndDestroy(EntityManager & entityManager, vector<int> components) {
  vector<shared_ptr<Entity>> targetEntities = entityManager.getEntitiesHasOneOf(entityManager.getComponentChecker(components));

  for (shared_ptr<Entity> targetEntity : targetEntities) {
    TransformComponent *transformComponent = targetEntity->getComponent<TransformComponent>();
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
