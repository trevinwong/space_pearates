#ifndef LIGHT_TOWER_ATTACK_COMPONENT_H
#define LIGHT_TOWER_ATTACK_COMPONENT_H

#include "Utility/utility.hpp"
#include "../base_component.hpp"
#include "fire_tower_attack_component.hpp"

class LightTowerAttackComponent : public TowerAttackComponent {
public:
  // Note: _fireRate (unit: s)
  LightTowerAttackComponent(vec2 _relativeFirePosition,
    float _attackRange,
    int _maxLevel,
    float _fireRate,
    int projectileAttackPower,
    int projectileNumberPerShoot);

  int getProjectileNumberPerShoot();

  virtual int getTowerType() { return towerTypeID; };

private:
  int projectileNumberPerShoot;
  static const int towerTypeID = TowerTypeID::light_tower;
};

#endif