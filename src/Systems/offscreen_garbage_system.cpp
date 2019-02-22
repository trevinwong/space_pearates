#include "offscreen_garbage_system.hpp"

OffscreenGarbageSystem::OffscreenGarbageSystem()
{
}

OffscreenGarbageSystem::~OffscreenGarbageSystem()
{
}

void OffscreenGarbageSystem::destroyOffScreenEntities(EntityManager & entityManager)
{
  vector<shared_ptr<Entity>> targetEntities =
    entityManager.getEntitiesHasOneOf(entityManager.getComponentChecker(this->targetEntitiesCharacterizedComponents));

  for (shared_ptr<Entity> targetEntity : targetEntities) {
    TransformComponent *transformComponent = targetEntity->getComponent<TransformComponent>();
    if (transformComponent == nullptr) continue;

    auto projectileLeftTopPositon = transformComponent->position;
    auto projectileSize = transformComponent->size;

    if ((projectileLeftTopPositon.x > SCREEN_WIDTH || projectileLeftTopPositon.x + projectileSize.x < 0.0) ||
      (projectileLeftTopPositon.y > SCREEN_HEIGHT || projectileLeftTopPositon.y + projectileSize.y < 0.0)) 
    {
      entityManager.removeEntity(targetEntity);
    }
  }
}
