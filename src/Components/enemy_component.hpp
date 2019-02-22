#ifndef ENEMY_COMPONENT_H
#define ENEMY_COMPONENT_H

#include "utility.hpp"
#include "base_component.hpp"

// For entities intended to be controled by the player.
// ATM, there should only ever be one entity with this component.
class EnemyComponent : public BaseComponent
{
public:
  EnemyComponent();
  ~EnemyComponent();
  static const int typeID = ComponentType::enemy;
  inline virtual int getTypeID() const { return typeID; };
};

#endif