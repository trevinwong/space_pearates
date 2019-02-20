#include "fire_tower_attack_component.hpp"


FireTowerAttackComponent::FireTowerAttackComponent(
  glm::vec2 _relativeFirePosition,
  float _attackRange,
  int _maxLevel,
  float _fireRate,
  int _projectileAttackPower
) :
  TowerAttackComponent(_relativeFirePosition, _attackRange, _fireRate),
  fireRate(_fireRate),
  projectileAttackPower(_projectileAttackPower),
  elapsedTimeToNextFire(_fireRate)
{
}

FireTowerAttackComponent::~FireTowerAttackComponent()
{
  TowerAttackComponent::~TowerAttackComponent();
}

float FireTowerAttackComponent::getElapsedTimeToNextFire()
{
  return this->elapsedTimeToNextFire;
}

void FireTowerAttackComponent::resetElapsedTimeToNextFire()
{
  this->elapsedTimeToNextFire = this->fireRate;
}

void FireTowerAttackComponent::reduceElapsedTimeToNextFire(float dt)
{
  // If the tower is already ready, then no need to reduce elapsed time
  if (this->isReadyForNextFire()) return;

  this->elapsedTimeToNextFire -= dt;
}

bool FireTowerAttackComponent::isReadyForNextFire()
{
  return this->getElapsedTimeToNextFire() <= 0.0;
}

float FireTowerAttackComponent::getFireRate()
{
  return this->fireRate;
}

int FireTowerAttackComponent::getProjectileAttackPower()
{
  return this->projectileAttackPower;
}
