#include "star_tower_attack_component.hpp"

StarTowerAttackComponent::StarTowerAttackComponent(vec2 _relativeFirePosition, vector<int> _attackPerLvl, vector<float> _rangePerLvl, vector<float> _fireRatePerLvl, vector<float> _sizePerLvl) :
  TowerAttackComponent(_relativeFirePosition, _attackPerLvl, _rangePerLvl, _fireRatePerLvl),
  sizePerLvl(_sizePerLvl)
{
  setToLevel(0);
}

void StarTowerAttackComponent::setToLevel(int level)
{
  attackRange = rangePerLvl[level];
  fireRate = fireRatePerLvl[level];
  projectileAttackPower = attackPerLvl[level]; 
  projectileSize = vec2(sizePerLvl[level], sizePerLvl[level]);
}

vec2 StarTowerAttackComponent::getProjectileSize()
{
  return projectileSize * SCALING_FACTOR;
}
