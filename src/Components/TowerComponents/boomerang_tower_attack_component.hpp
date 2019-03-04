#ifndef BOOMERANG_TOWER_ATTACK_COMPONENT_H
#define BOOMERANG_TOWER_ATTACK_COMPONENT_H

#include "utility.hpp"
#include "../base_component.hpp"
#include "tower_attack_component.hpp"

class BoomerangTowerAttackComponent : public TowerAttackComponent {
public:
  BoomerangTowerAttackComponent(
    vec2 _relativeFirePosition,
    float _attackRange,
    int _maxLevel,
    float _fireRate,
    int _projectileAttackPower);

  virtual int getTowerType() { return towerTypeID; };

private:
  static const int towerTypeID = TowerTypeID::boomerang_tower;
};

#endif
