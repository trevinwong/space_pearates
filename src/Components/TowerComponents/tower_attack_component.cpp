#include "tower_attack_component.hpp"

TowerAttackComponent::TowerAttackComponent(vec2 _relativeFirePosition, vector<int> _attackPerLvl, vector<float> _rangePerLvl, vector<float> _fireRatePerLvl) :
  relativeFirePosition(_relativeFirePosition),
  attackPerLvl(_attackPerLvl),
  rangePerLvl(_rangePerLvl),
  fireRatePerLvl(_fireRatePerLvl) 
{
  elapsedTimeToNextFire = 0;
  projectileAttackPower = attackPerLvl[0];
  attackRange = rangePerLvl[0];
  fireRate = fireRatePerLvl[0]; 
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
  return attackRange;
}

float TowerAttackComponent::getFireRate()
{
  return this->fireRate;
}

int TowerAttackComponent::getProjectileAttackPower()
{
  return this->projectileAttackPower;
}
