#include "water_tower_attack_component.hpp"

WaterTowerAttackComponent::WaterTowerAttackComponent(
  glm::vec2 _relativeFirePosition, 
  float _attackRange, 
  int _maxLevel, 
  float _slowDownFactor
):
  // a water tower does not have attack rate and power
  TowerAttackComponent(_relativeFirePosition, _attackRange, _maxLevel, 0.0, 0),
    slowDownFactor(_slowDownFactor)
{
}

float WaterTowerAttackComponent::getSlowDownFactor()
{
  // as water tower level goes up, slow down power get stronger
  return slowDownFactor  -  0.05f * (float)(currentLevel);
}
