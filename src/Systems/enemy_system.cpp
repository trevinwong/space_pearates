#include "enemy_system.hpp"

// Super simple AI; just tries to go down the map until it hits base
// If it can't go down anymore, randomly goes right / left till it can go down
void EnemySystem::move (float dt, EntityManager& entityManager) {
  srand(time(NULL));
  int arr[2] = {-1, 1};

void EnemySystem::move (float dt, EntityManager& entityManager) {
  vector<shared_ptr<Entity>> entityList = entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::transform, ComponentType::enemy, ComponentType::movement}));
  for (shared_ptr<Entity> e : entityList) {
    EnemyPathComponent *pathfind = e->getComponent<EnemyPathComponent>();
    if (pathfind) {
      pathfind->move(dt, entityManager);
    }
  }
}

bool EnemySystem::setMap (EntityManager& entityManager) {
  shared_ptr<Entity> e = entityManager.getEntitiesHasOneOf(entityManager.getComponentChecker(vector<int>{ComponentType::map}))[0];
	shared_ptr<MapComponent> mapComponent = e->getComponent<MapComponent>();
  if (!mapComponent) return false;
  map = mapComponent->mapData2DArray;
  return true;
}