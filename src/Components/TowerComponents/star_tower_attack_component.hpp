#ifndef STAR_TOWER_ATTACK_COMPONENT_H
#define STAR_TOWER_ATTACK_COMPONENT_H

#include "utility.hpp"
#include "../base_component.hpp"
#include "tower_attack_component.hpp"

class StarTowerAttackComponent : public TowerAttackComponent {
public:
  // Note: _fireRate (unit: s)
  StarTowerAttackComponent(vec2 _relativeFirePosition,
    float _attackRange,
    int _maxLevel,
    float _fireRate,
    int projectileAttackPower,
    vec2 projectileSize);

  virtual int getTowerType() { return towerTypeID; };

  vec2 getProjectileSize();

private:
  vec2 projectileSize;
  static const int towerTypeID = TowerTypeID::star_tower;
};

#endif