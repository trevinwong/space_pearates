#ifndef LIGHT_TOWER_ATTACK_COMPONENT_H
#define LIGHT_TOWER_ATTACK_COMPONENT_H

#include "utility.hpp"
#include "../base_component.hpp"
#include "fire_tower_attack_component.hpp"

/*
  LightTowerAttackComponent is similiar to FireTowerAttackComponent
  Light Tower can shoot multi-projectiles once
  However Light Tower cannot aim enemies
*/
class LightTowerAttackComponent : public FireTowerAttackComponent {
public:
  // Note: _shootRate (unit: s)
  LightTowerAttackComponent(glm::vec2 _relativeFirePosition, float _attackRange, int _maxLevel, float _fireRate, int projectileAttackPower, int projectileNumberPerShoot);
  ~LightTowerAttackComponent();

  int getProjectileNumberPerShoot();

  static const int typeID = ComponentType::light_tower;
  virtual int getTypeID() const { return typeID; };

private:
  int projectileNumberPerShoot;
};

#endif