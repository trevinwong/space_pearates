#include "tower_attack_component.hpp"

TowerAttackComponent::TowerAttackComponent(glm::vec2 _relativeFirePosition, float _attackRange, int _maxLevel) :
  relativeFirePosition(_relativeFirePosition),
  attackRange(_attackRange),
  maxLevel(_maxLevel),
  currentLevel(0) // initial to level 0
{
}

glm::vec2 TowerAttackComponent::getRelativeFirePosition()
{
  return this->relativeFirePosition;
}

int TowerAttackComponent::getAttackRange()
{
  return this->attackRange;
}

int TowerAttackComponent::getCurrentLevel()
{
  return this->currentLevel;
}

int TowerAttackComponent::getMaxLevel()
{
  return this->maxLevel;
}
