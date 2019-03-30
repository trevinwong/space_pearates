#ifndef FIRE_TOWER_ATTACK_COMPONENT_H
#define FIRE_TOWER_ATTACK_COMPONENT_H

#include "Utility/utility.hpp"
#include "../base_component.hpp"
#include "tower_attack_component.hpp"

class FireTowerAttackComponent : public TowerAttackComponent {
public:
  FireTowerAttackComponent(vec2 _relativeFirePosition, vector<int> _attackPerLvl, vector<float> _rangePerLvl, vector<float> _fireRatePerLvl);

  virtual void setToLevel(int level);
  virtual int getTowerType() { return towerTypeID; };
private:
  static const int towerTypeID = TowerTypeID::fire_tower;
};

#endif
