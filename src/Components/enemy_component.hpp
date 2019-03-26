#ifndef ENEMY_COMPONENT_H
#define ENEMY_COMPONENT_H

#include "Utility/utility.hpp"
#include "base_component.hpp"

class EnemyComponent : public BaseComponent
{
public:
	int worth;
	int baseAtk = 20;
	int totalAtk;

  EnemyComponent(int _worth, float _atkMult);
  ~EnemyComponent();
  static const int typeID = ComponentType::enemy;
  inline virtual int getTypeID() const { return typeID; };
};

#endif
