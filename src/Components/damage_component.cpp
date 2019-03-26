#include "damage_component.hpp"

DamageComponent::DamageComponent(float damage)
{
	damage_instances.push_back(damage);
}

void DamageComponent::addDamageInstance(float damage)
{
	damage_instances.push_back(damage);
}
