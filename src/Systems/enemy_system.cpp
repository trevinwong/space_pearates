#include "enemy_system.hpp"

Enemy::Enemy()
{
  factory = EnemyFactory();
}


/// map is 32x20
Enemy::~Enemy()
{
}

void Enemy::loadEnemy(glm::vec2 screen, EntityManager& entities) {
  entities.addEntity(factory.build(vec2(screen.x / 2, 5), vec2(16,16), vec2(0.f, 40.f)));
}


// Super simple AI; just tries to go down the map until it hits base
// Keeps trying to go right until it can't, then goes left.
void Enemy::move (float dt, EntityManager& entities) {
  vector<shared_ptr<Entity>> entityList = entities.getEntities();
  float eps = 0.001;
  for (shared_ptr<Entity> e : entityList) {
    MovementComponent *movementComponent = e->getComponent<MovementComponent>();
    EnemyComponent *enemyComponent = e->getComponent<EnemyComponent>();
    TransformComponent *transformComponent = e->getComponent<TransformComponent>();

    if (enemyComponent && movementComponent && transformComponent) {
      vec2 vel = movementComponent->velocity;
      vec2 pos = transformComponent->position;
      int yind = static_cast<int>(pos.y / 40);
      int xind = static_cast<int>(pos.x / 40);
      bool flag = false;
      vel.y = abs(vel.y) < eps ? movementComponent->maxVelocity.y : vel.y;

      for (int i = 0; i <= ceil(vel.y*dt/40); i++)
        if (map[yind+i][xind] == 'B')
          flag = true;

      if (flag) {
        vel.x = abs(vel.x) < eps ? movementComponent->maxVelocity.x : vel.x;
        if (vel.x > 0)
          vel.x = pos.x + vel.x*dt < 1200.0 ? vel.x : -vel.x;
        else vel.x = pos.x + vel.x*dt > 60 ? vel.x : -vel.x;
        vel.y = 0;
      }
      for (int i = 0; i <= ceil(vel.y*dt/40); i++)
        if (map[yind+i][xind] == 'H') {
          vel.y = 2*movementComponent->maxVelocity.y;
          movementComponent->maxVelocity.x = 0.f;
        }
      movementComponent->velocity = vel;
    }
  }
}


void Enemy::getMap (EntityManager& entities) {
  vector<shared_ptr<Entity>> entityList = entities.getEntities();
  for (shared_ptr<Entity> e: entityList) {
    MapComponent *mapComponent = e->getComponent<MapComponent>();
    if (!mapComponent) continue;
    map = mapComponent->mapData2DArray;
  }
}