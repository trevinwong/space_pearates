#ifndef ENEMY_COMPONENT_H
#define ENEMY_COMPONENT_H

#include "utility.hpp"
#include "base_component.hpp"

class EnemyComponent : public BaseComponent
{
public:
	int worth;
  EnemyComponent(int _worth);
  ~EnemyComponent();
  static const int typeID = ComponentType::enemy;
  inline virtual int getTypeID() const { return typeID; };
};

#endif
