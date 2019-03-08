#include "light_tower_attack_component.hpp"

LightTowerAttackComponent::LightTowerAttackComponent(
  vec2 _relativeFirePosition,
  float _attackRange,
  int _maxLevel,
  float _fireRate,
  int _projectileAttackPower,
  int _projectileNumberPerShoot
) :
  TowerAttackComponent(_relativeFirePosition, _attackRange, _maxLevel, _fireRate, _projectileAttackPower),
  projectileNumberPerShoot(_projectileNumberPerShoot)
{
}

int LightTowerAttackComponent::getProjectileNumberPerShoot()
{
  // light tower can shoot more in upper levels
  return this->projectileNumberPerShoot * (currentLevel + 1);
}
