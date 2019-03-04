#include "tower_attack_component.hpp"

TowerAttackComponent::TowerAttackComponent(vec2 _relativeFirePosition, float _attackRange, int _maxLevel, float _fireRate, int _projectileAttackPower) :
  relativeFirePosition(_relativeFirePosition),
  attackRange(_attackRange),
  maxLevel(_maxLevel),
  currentLevel(0), // initial to level 0
  fireRate(_fireRate),
  elapsedTimeToNextFire(_fireRate),
  projectileAttackPower(_projectileAttackPower)
{
}

void TowerAttackComponent::resetElapsedTimeToNextFire()
{
  elapsedTimeToNextFire = getFireRate();
}

void TowerAttackComponent::reduceElapsedTimeToNextFire(float dt)
{
  // If the tower is already ready, then no need to reduce elapsed time
  if (isReadyForNextFire()) return;

  elapsedTimeToNextFire -= dt;
}

bool TowerAttackComponent::isReadyForNextFire()
{
  return elapsedTimeToNextFire <= 0.0;
}

float TowerAttackComponent::getAttackRange()
{
  return attackRange + currentLevel * 20.0f;
}

float TowerAttackComponent::getFireRate()
{
  return this->fireRate - currentLevel * 0.2f;
}

int TowerAttackComponent::getProjectileAttackPower()
{
  return this->projectileAttackPower + currentLevel * 5.0f;
}
