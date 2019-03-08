#ifndef FIRE_TOWER_ATTACK_COMPONENT_H
#define FIRE_TOWER_ATTACK_COMPONENT_H

#include "utility.hpp"
#include "../base_component.hpp"
#include "tower_attack_component.hpp"

class FireTowerAttackComponent : public TowerAttackComponent {
public:
  // Note: _shootRate (unit: s)
  FireTowerAttackComponent(vec2 _relativeFirePosition, float _attackRange, int _maxLevel, float _fireRate, int _projectileAttackPower);

  virtual int getTowerType() { return towerTypeID; };

private:
  static const int towerTypeID = TowerTypeID::fire_tower;
};

#endif
