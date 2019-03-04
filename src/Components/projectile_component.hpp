#ifndef PROJECTILE_COMPONENT_H
#define PROJECTILE_COMPONENT_H

#include "utility.hpp"
#include "base_component.hpp"

class ProjectileComponent : public BaseComponent {
public:
  ProjectileComponent(int _attackPower, bool _rotateOn=false);
  int getAttackPower();
  bool rotateOn;

  inline virtual int getTypeID() const { return typeID; };
  static const int typeID = ComponentType::projectile;

private:
  int attactPower;
};

#endif // !PROJECTILE_COMPONENT_H
