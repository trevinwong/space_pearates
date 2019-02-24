#include "tower_attack_system.hpp"

TowerAttackSystem::TowerAttackSystem() {

}

TowerAttackSystem::~TowerAttackSystem() {

}

void TowerAttackSystem::checkRangeAndShootProjectiles(EntityManager& entityManager) {

  vector<shared_ptr<Entity>> enemyEntities =
    entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::enemy}));
  vector<shared_ptr<Entity>> towerEntities =
    entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::attack_tower}));

  // no enemies or no towers in the world now
  if (enemyEntities.size() == 0 || towerEntities.size() == 0) return;

  // Loop all towers
  for (shared_ptr<Entity> towerEntity : towerEntities) {

    SpriteComponent *spriteComponent = towerEntity->getComponent<SpriteComponent>();
    TransformComponent *transformComponent = towerEntity->getComponent<TransformComponent>();
    TowerAttackComponent *towerAttackComponent = towerEntity->getComponent<TowerAttackComponent>();

    // check null here
    if (spriteComponent == nullptr || transformComponent == nullptr || towerAttackComponent == nullptr) continue;

    // calculate the fire point position
    glm::vec2 towerLeftTopPosition = transformComponent->position;
    glm::vec2 towerSize = transformComponent->size;
    glm::vec2 towerCenterPosition = towerLeftTopPosition + towerSize * 0.5f;
    glm::vec2 relativeFirePosition = towerAttackComponent->relativeFirePosition;
    glm::vec2 firePointPosition(towerCenterPosition + towerSize * relativeFirePosition);

    // loop all
    float towerRadius = towerAttackComponent->getAttackRange();
    for (shared_ptr<Entity> enemyEntity : enemyEntities) {
      TransformComponent *enemyTransformComponent = enemyEntity->getComponent<TransformComponent>();
      glm::vec2 enemyPosition = enemyTransformComponent->position;
      glm::vec2 enemyCenterPosition = enemyPosition + enemyTransformComponent->size * 0.5f;
      float enemyHitboxRadius = glm::max(enemyTransformComponent->size.x, enemyTransformComponent->size.y);

      // calcule distance
      float centerOfCircleDist = glm::distance(enemyCenterPosition, firePointPosition);
      float radiusSum = enemyHitboxRadius + towerRadius;

      if (centerOfCircleDist < radiusSum && towerAttackComponent->isReadyForNextFire()) {

        if (towerAttackComponent->getTowerType() == TowerTypeID::fire_tower) {
          // in the range, FIRE!
          auto projectileSize = glm::vec2(15.0, 15.0);
          auto projectileColor = glm::vec4(1, 1, 1, 1);
          auto projectileLeftTopPosition = firePointPosition - projectileSize * 0.5f;
          auto speed = 100.0f;
          auto velocityDirection = glm::normalize(enemyCenterPosition - firePointPosition);
          auto attackPower = 10;
          Entity projectileEntity =
            ProjectileEntityFactory::createAimProjectile(projectileSize, projectileColor, projectileLeftTopPosition, speed, velocityDirection, attackPower);

          entityManager.addEntity(projectileEntity);
          // fired, wait until next time to fire
          towerAttackComponent->resetElapsedTimeToNextFire();
        }
        else if (towerAttackComponent->getTowerType() == TowerTypeID::light_tower) {
          // in the range, FIRE!
          auto projectileNumberPerShoot = dynamic_cast<LightTowerAttackComponent*>(towerAttackComponent)->getProjectileNumberPerShoot();
          auto projectileSize = glm::vec2(15.0, 15.0);
          auto projectileColor = glm::vec4(1, 1, 1, 1);
          auto projectileLeftTopPosition = firePointPosition - projectileSize * 0.5f;
          auto speed = 100.0f;
          auto attackPower = 10;
          vector<Entity> projectileEntities =
            ProjectileEntityFactory::createSpreadProjectiles(projectileNumberPerShoot, projectileSize, projectileColor, projectileLeftTopPosition, speed, attackPower);

          for (Entity projectile : projectileEntities)
            entityManager.addEntity(projectile);
          // fired, wait until next time to fire
          towerAttackComponent->resetElapsedTimeToNextFire();
        }

      }
    }
  }
}

void TowerAttackSystem::reduceElapsedTimeToNextFire(EntityManager & entityManager, float dt)
{
  vector<shared_ptr<Entity>> fireTowerEntities =
    entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::tower_meta}));

  for (shared_ptr<Entity> fireTowerEntity : fireTowerEntities) {
    FireTowerAttackComponent *fireTowerAttackComponent = fireTowerEntity->getComponent<FireTowerAttackComponent>();
    if (fireTowerAttackComponent != nullptr) fireTowerAttackComponent->reduceElapsedTimeToNextFire(dt);

    LightTowerAttackComponent *lightTowerAttackComponent = fireTowerEntity->getComponent<LightTowerAttackComponent>();
    if (lightTowerAttackComponent != nullptr) lightTowerAttackComponent->reduceElapsedTimeToNextFire(dt);
  }
}
