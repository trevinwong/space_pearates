#include "tower_attack_system.hpp"

void TowerAttackSystem::checkRangeAndShootProjectiles(EntityManager& entityManager) {

  vector<shared_ptr<Entity>> enemyEntities = entityManager.getEntities(entityManager.getComponentChecker(
    vector<int> {ComponentType::enemy, ComponentType::transform}));
  vector<shared_ptr<Entity>> towerEntities = entityManager.getEntities(entityManager.getComponentChecker(
    vector<int> {ComponentType::attack_tower, ComponentType::sprite, ComponentType::transform}));

  // no enemies or no towers in the world now
  if (enemyEntities.size() == 0 || towerEntities.size() == 0) return;

  // Loop all enemies
  for (shared_ptr<Entity> enemyEntity : enemyEntities) {
    shared_ptr<TransformComponent> enemyTransformComponent = enemyEntity->getComponent<TransformComponent>();
    if (enemyTransformComponent == nullptr) continue;

    vec2 enemyPosition = enemyTransformComponent->position;
    vec2 enemyCenterPosition = enemyPosition + enemyTransformComponent->size * 0.5f;
    float enemyHitboxRadius = glm::max(enemyTransformComponent->size.x, enemyTransformComponent->size.y);

    // each time we check if an enmey is in water tower attack range,
    // we assume the enemy is not.
    // Reset its water tower factor
    // then, if it is in any water tower range, the tower loop below will update the factor
    auto waterTowerFactorComponent = enemyEntity->getComponent<WaterTowerFactorComponent>();
    if (waterTowerFactorComponent != nullptr) {
      // here, reset the water tower factor
      waterTowerFactorComponent->speedFactor = 1.0f;
    }

    // Loop all towers
    for (shared_ptr<Entity> towerEntity : towerEntities) {

      shared_ptr<SpriteComponent> spriteComponent = towerEntity->getComponent<SpriteComponent>();
      shared_ptr<TransformComponent> transformComponent = towerEntity->getComponent<TransformComponent>();
      shared_ptr<TowerAttackComponent> towerAttackComponent = towerEntity->getComponent<TowerAttackComponent>();

      // check null here
      if (spriteComponent == nullptr || transformComponent == nullptr || towerAttackComponent == nullptr) continue;

      // calculate the fire point position
      vec2 towerLeftTopPosition = transformComponent->position;
      vec2 towerSize = transformComponent->size;
      vec2 towerCenterPosition = towerLeftTopPosition + towerSize * 0.5f;
      vec2 relativeFirePosition = towerAttackComponent->relativeFirePosition;
      vec2 firePointPosition(towerCenterPosition + towerSize * relativeFirePosition);

      float towerRadius = towerAttackComponent->getAttackRange();

      // calculate distance
      float centerOfCircleDist = glm::distance(enemyCenterPosition, firePointPosition);
      float radiusSum = enemyHitboxRadius + towerRadius;

      if (centerOfCircleDist < radiusSum && towerAttackComponent->isReadyForNextFire()) {
        // in the range, FIRE!
        switch (towerAttackComponent->getTowerType())
        {
        case TowerTypeID::fire_tower:
        {
          auto projectileSize = vec2(15.0, 15.0);
          auto projectileColor = glm::vec4(1, 1, 1, 1);
          auto projectileLeftTopPosition = firePointPosition - projectileSize * 0.5f;
          auto speed = 100.0f;
          auto velocityDirection = glm::normalize(enemyCenterPosition - firePointPosition);
          auto attackPower = towerAttackComponent->getProjectileAttackPower();
          Entity projectileEntity = ProjectileEntityFactory::createAimProjectile(
            projectileSize, projectileColor, projectileLeftTopPosition, speed, velocityDirection, attackPower);

          entityManager.addEntity(projectileEntity);
          // fired, wait until next time to fire
          towerAttackComponent->resetElapsedTimeToNextFire();
          break;
        }
        case TowerTypeID::light_tower:
        {
          auto projectileNumberPerShoot = std::dynamic_pointer_cast<LightTowerAttackComponent>(towerAttackComponent)->getProjectileNumberPerShoot();
          auto projectileSize = vec2(15.0, 15.0);
          auto projectileColor = glm::vec4(1, 1, 1, 1);
          auto projectileLeftTopPosition = firePointPosition - projectileSize * 0.5f;
          auto speed = 240.0f;
          auto attackPower = towerAttackComponent->getProjectileAttackPower();
          vector<Entity> projectileEntities = ProjectileEntityFactory::createSpreadProjectiles(
            projectileNumberPerShoot, projectileSize, projectileColor, projectileLeftTopPosition, speed, attackPower);

          for (Entity projectile : projectileEntities)
            entityManager.addEntity(projectile);
          // fired, wait until next time to fire
          towerAttackComponent->resetElapsedTimeToNextFire();
          break;
        }
        case TowerTypeID::star_tower:
        {
          auto projectileSize = std::dynamic_pointer_cast<StarTowerAttackComponent>(towerAttackComponent)->getProjectileSize();
          auto projectileColor = glm::vec4(1, 1, 1, 1);
          auto projectileLeftTopPosition = firePointPosition - projectileSize * 0.5f;
          vec2 velocity = glm::normalize(enemyCenterPosition - firePointPosition) * 400.0f;
          vec2 acc = vec2(0, 0);
          vec2 maxVelocity = vec2(1000.0f, 1000.0f);
          vec2 maxAcc = vec2(0.0f, 1000.0f);
          auto attackPower = towerAttackComponent->getProjectileAttackPower();
          Entity projectileEntity = ProjectileEntityFactory::createStarProjectile(
            projectileSize, projectileColor, projectileLeftTopPosition, velocity, acc, maxVelocity, maxAcc, attackPower);

          entityManager.addEntity(projectileEntity);
          // fired, wait until next time to fire
          towerAttackComponent->resetElapsedTimeToNextFire();
          break;
        }
        case TowerTypeID::boomerang_tower:
        {
          auto attackPower = towerAttackComponent->getProjectileAttackPower();
          Entity projectileEntity = ProjectileEntityFactory::createBoomerang(
            firePointPosition, enemyCenterPosition, attackPower);

          entityManager.addEntity(projectileEntity);
          // fired, wait until next time to fire
          towerAttackComponent->resetElapsedTimeToNextFire();
          break;
        }
        case TowerTypeID::water_tower:
        {
          // in the range, slow it down!
          float slowDownFactor = std::dynamic_pointer_cast<WaterTowerAttackComponent>(towerAttackComponent)->getSlowDownFactor();
          if (waterTowerFactorComponent != nullptr) {
            // if an enemy is in the overlap of two water towers, then we pickup the smallest factor
            waterTowerFactorComponent->speedFactor = glm::min(waterTowerFactorComponent->speedFactor, slowDownFactor);
          }
          // Note: water tower does not have fire rate
          break;
        }
        default:
          break;
        }
      }
    }
  }
}

void TowerAttackSystem::reduceElapsedTimeToNextFire(EntityManager & entityManager, float dt)
{
  vector<shared_ptr<Entity>> towerEntities = entityManager.getEntities(entityManager.getComponentChecker(
    vector<int> {ComponentType::tower_meta}));

  for (shared_ptr<Entity> towerEntity : towerEntities) {
    shared_ptr<FireTowerAttackComponent> fireTowerAttackComponent = towerEntity->getComponent<FireTowerAttackComponent>();
    if (fireTowerAttackComponent != nullptr) fireTowerAttackComponent->reduceElapsedTimeToNextFire(dt);

    shared_ptr<LightTowerAttackComponent> lightTowerAttackComponent = towerEntity->getComponent<LightTowerAttackComponent>();
    if (lightTowerAttackComponent != nullptr) lightTowerAttackComponent->reduceElapsedTimeToNextFire(dt);

    shared_ptr<StarTowerAttackComponent> starTowerAttackComponent = towerEntity->getComponent<StarTowerAttackComponent>();
    if (starTowerAttackComponent != nullptr) starTowerAttackComponent->reduceElapsedTimeToNextFire(dt);

    shared_ptr<BoomerangTowerAttackComponent> boomerangTowerAttackComponent = towerEntity->getComponent<BoomerangTowerAttackComponent>();
    if (boomerangTowerAttackComponent != nullptr) boomerangTowerAttackComponent->reduceElapsedTimeToNextFire(dt);
  }
}
