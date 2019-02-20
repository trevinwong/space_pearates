#include "tower_attack_system.hpp"

TowerAttackSystem::TowerAttackSystem() {
  
}

TowerAttackSystem::~TowerAttackSystem() {

}

void TowerAttackSystem::checkRangeAndShootAimProjectiles(EntityManager& entityManager) {

  // FIXME: so far use player to test shooting system, change to use enemies
  vector<shared_ptr<Entity>> enemyEntities =
    entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::player}));
  vector<shared_ptr<Entity>> towerEntities =
    entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::fire_tower}));

  // no enemies or no towers in the world now
  if (enemyEntities.size() == 0 || towerEntities.size() == 0) return;

  // Loop all towers
  for (shared_ptr<Entity> towerEntity : towerEntities) {

    SpriteComponent *spriteComponent = towerEntity->getComponent<SpriteComponent>();
    TransformComponent *transformComponent = towerEntity->getComponent<TransformComponent>();
    FireTowerAttackComponent *fireTowerAttackComponent = towerEntity->getComponent<FireTowerAttackComponent>();

    // check null here
    if (spriteComponent == nullptr || transformComponent == nullptr || fireTowerAttackComponent == nullptr) continue;

    // calculate the fire point position
    glm::vec2 towerLeftTopPosition = transformComponent->position;
    glm::vec2 towerSize = transformComponent->size;
    glm::vec2 towerCenterPosition = towerLeftTopPosition + towerSize * 0.5f;
    glm::vec2 relativeFirePosition = fireTowerAttackComponent->getRelativeFirePosition();
    glm::vec2 firePointPosition(towerCenterPosition + towerSize * relativeFirePosition);

    float towerRadius = fireTowerAttackComponent->getAttackRange();
    
    // loop all 
    for (shared_ptr<Entity> enemyEntity : enemyEntities) {
      TransformComponent *enemyTransformComponent = enemyEntity->getComponent<TransformComponent>();
      glm::vec2 enemyPosition = enemyTransformComponent->position;
      glm::vec2 enemyCenterPosition = enemyPosition + enemyTransformComponent->size * 0.5f;
      float enemyHitboxRadius = glm::max(enemyTransformComponent->size.x, enemyTransformComponent->size.y);

      // calcule distance
      float centerOfCircleDist = glm::distance(enemyCenterPosition, firePointPosition);
      float radiusSum = enemyHitboxRadius + towerRadius;

      if (centerOfCircleDist < radiusSum && fireTowerAttackComponent->isReadyForNextFire()) {
        // in the range, FIRE!
        auto projectileSize = glm::vec2(15.0, 15.0);
        auto projectileColor = glm::vec4(1, 1, 1, 1);
        auto projectileLeftTopPosition = firePointPosition - projectileSize * 0.5f;
        auto speed = 100.0f;
        auto velocityDirection = glm::normalize(enemyCenterPosition - firePointPosition) * 100.0f;
        auto attackPower = 10;
        Entity projectileEntity =
          ProjectileEntityFactory::createAimProjectile(projectileSize, projectileColor, projectileLeftTopPosition, speed, velocityDirection, attackPower);

        entityManager.addEntity(projectileEntity);
        // fired, wait until next time to fire
        fireTowerAttackComponent->resetElapsedTimeToNextFire();
      }
    }
  }
}

void TowerAttackSystem::reduceElapsedTimeToNextFire(EntityManager & entityManager, float dt)
{
  vector<shared_ptr<Entity>> fireTowerEntities =
    entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::fire_tower}));

  for (shared_ptr<Entity> fireTowerEntity : fireTowerEntities) {
    FireTowerAttackComponent *fireTowerAttackComponent = fireTowerEntity->getComponent<FireTowerAttackComponent>();
    if (fireTowerAttackComponent == nullptr) continue;

    fireTowerAttackComponent->reduceElapsedTimeToNextFire(dt);
  }
}