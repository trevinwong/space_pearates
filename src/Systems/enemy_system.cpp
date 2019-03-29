#include "enemy_system.hpp"

void EnemySystem::move (float dt, EntityManager& entityManager) {
  vector<shared_ptr<Entity>> entityList = entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::transform, ComponentType::enemy, ComponentType::movement}));
  for (shared_ptr<Entity> e : entityList) {
    shared_ptr<EnemyPathComponent> pathfind = e->getComponent<EnemyPathComponent>();
    if (pathfind) {
      pathfind->move(dt, entityManager);
    }
  }
}

bool EnemySystem::setMap (EntityManager& entityManager) {
  shared_ptr<Entity> e = entityManager.getEntitiesHasOneOf(entityManager.getComponentChecker(vector<int>{ComponentType::map}))[0];
  shared_ptr<MapComponent> mapComponent = e->getComponent<MapComponent>();
  tiles = entityManager.getEntities(entityManager.getComponentChecker(vector<int>{ComponentType::tile}));
  if (!mapComponent) return false;
  map = mapComponent->mapData2DArray;
  return true;
}