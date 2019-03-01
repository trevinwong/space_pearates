#ifndef WATER_TOWER_ATTACK_COMPONENT_H
#define WATER_TOWER_ATTACK_COMPONENT_H

#include "utility.hpp"
#include "../base_component.hpp"
#include "tower_attack_component.hpp"

class WaterTowerAttackComponent : public TowerAttackComponent {
public:
  // Note: _shootRate (unit: s)
  WaterTowerAttackComponent(glm::vec2 _relativeFirePosition, 
                            float _attackRange, 
                            int _maxLevel,
                            float _slowDownFactor);

  float getSlowDownFactor();
  virtual int getTowerType() { return towerTypeID; };

private:
  float slowDownFactor;
  static const int towerTypeID = TowerTypeID::water_tower;
};

#endif