#include "projectile_component.hpp"

ProjectileComponent::ProjectileComponent(int _attackPower, bool _rotateOn) :
  attactPower(_attackPower), rotateOn(_rotateOn)
{
  cout << rotateOn << endl;
}

int ProjectileComponent::getAttackPower()
{
  return this->attactPower;
}
