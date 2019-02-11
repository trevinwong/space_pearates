#include "enemy.hpp"

Enemy::Enemy()
{
  factory = EnemyFactory();
  speed = 2.0;
}

Enemy::~Enemy()
{
}

void Enemy::loadEnemy(glm::vec2 screen, EntityManager& entities) {
  entities.addEntity(factory.build(glm::vec2(screen.x / 2, 5), glm::vec2(16,16)));
}

void Enemy::move (float dt) {

}

void Enemy::getMap (EntityManager& entities) {
  vector<shared_ptr<Entity>> entityList = entities.getEntities();
  for (shared_ptr<Entity> e: entityList) {
    MapComponent *mapComponent = e->getComponent<MapComponent>();
    if (!mapComponent) continue;
    map = mapComponent->mapData2DArray;
  }
}
