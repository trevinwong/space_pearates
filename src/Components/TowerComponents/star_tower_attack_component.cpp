#include "star_tower_attack_component.hpp"

StarTowerAttackComponent::StarTowerAttackComponent(
  glm::vec2 _relativeFirePosition,
  float _attackRange,
  int _maxLevel,
  float _fireRate,
  int _projectileAttackPower,
  vec2 _projectileSize
) :
  TowerAttackComponent(_relativeFirePosition, _attackRange, _maxLevel, _fireRate, _projectileAttackPower),
  projectileSize(_projectileSize)
{
}

vec2 StarTowerAttackComponent::getProjectileSize()
{
  // star projectile gets bigger after upgrade
  return projectileSize + projectileSize * (float)(currentLevel + 1) * 2.0f;
}
