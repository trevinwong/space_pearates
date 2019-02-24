#include "fire_tower_attack_component.hpp"

FireTowerAttackComponent::FireTowerAttackComponent(
  glm::vec2 _relativeFirePosition,
  float _attackRange,
  int _maxLevel,
  float _fireRate,
  int _projectileAttackPower
) :
  TowerAttackComponent(_relativeFirePosition, _attackRange, _maxLevel, _fireRate, _projectileAttackPower)
{
}


