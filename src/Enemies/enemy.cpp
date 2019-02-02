#include "enemy.hpp"

Enemy::Enemy()
{
  factory = EnemyFactory();
}

Enemy::~Enemy()
{
}

void Enemy::loadEnemy(glm::vec2 screen, EntityManager& entities) {
  entities.addEntity(factory.build(glm::vec2(screen.x / 2, 5), glm::vec2(16,16)));
}

void Enemy::move () {

}