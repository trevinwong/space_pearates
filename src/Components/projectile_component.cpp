#include "projectile_component.hpp"

ProjectileComponent::ProjectileComponent(int _attackPower):
  attactPower(_attackPower)
{
  
}

ProjectileComponent::~ProjectileComponent()
{
}

int ProjectileComponent::getAttackPower()
{
  return this->attactPower;
}
