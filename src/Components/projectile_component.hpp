#ifndef PROJECTILE_COMPONENT_H
#define PROJECTILE_COMPONENT_H

#include "utility.hpp"
#include "base_component.hpp"

class ProjectileComponent : public BaseComponent {
  public:
    ProjectileComponent(int _attackPower);
    ~ProjectileComponent();
    int getAttackPower();

    static const int typeID = ComponentType::projectile;
    inline virtual int getTypeID() const { return typeID; };

  private:
    int attactPower;
};

#endif // !PROJECTILE_COMPONENT_H
