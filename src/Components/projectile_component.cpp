#include "projectile_component.hpp"

ProjectileComponent::ProjectileComponent(int _attackPower, bool _rotateOn) :
  attactPower(_attackPower), rotateOn(_rotateOn)
{
}

int ProjectileComponent::getAttackPower()
{
  return this->attactPower;
}
