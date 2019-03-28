#include "light_tower_attack_component.hpp"

LightTowerAttackComponent::LightTowerAttackComponent(vec2 _relativeFirePosition, vector<int> _attackPerLvl, vector<float> _rangePerLvl, vector<float> _fireRatePerLvl, vector<int> _numProjectilesPerLvl) :
  TowerAttackComponent(_relativeFirePosition, _attackPerLvl, _rangePerLvl, _fireRatePerLvl),
  numProjectilesPerLvl(_numProjectilesPerLvl)
{
  setToLevel(0);
}

void LightTowerAttackComponent::setToLevel(int level)
{
  attackRange = rangePerLvl[level];
  fireRate = fireRatePerLvl[level];
  projectileAttackPower = attackPerLvl[level]; 
  projectileNumberPerShoot = numProjectilesPerLvl[level];
}

int LightTowerAttackComponent::getProjectileNumberPerShoot()
{
  return this->projectileNumberPerShoot;
}
