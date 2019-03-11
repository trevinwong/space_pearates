#include "enemy_component.hpp"

EnemyComponent::EnemyComponent(int _worth, float _atkMult)
{
	worth =_worth;
	totalAtk = std::max(1, (int)(baseAtk * _atkMult));
}


EnemyComponent::~EnemyComponent()
{
}
