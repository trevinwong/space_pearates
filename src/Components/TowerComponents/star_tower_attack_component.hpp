#ifndef STAR_TOWER_ATTACK_COMPONENT_H
#define STAR_TOWER_ATTACK_COMPONENT_H

#include "Utility/utility.hpp"
#include "../base_component.hpp"
#include "tower_attack_component.hpp"

class StarTowerAttackComponent : public TowerAttackComponent {
public:
  StarTowerAttackComponent(vec2 _relativeFirePosition, vector<int> _attackPerLvl, vector<float> _rangePerLvl, vector<float> _fireRatePerLvl, vector<float> _sizePerLvl);

  virtual int getTowerType() { return towerTypeID; };
  virtual void setToLevel(int level);

  vec2 getProjectileSize();
  vec2 projectileSize;
  vector<float> sizePerLvl;

private:
  static const int towerTypeID = TowerTypeID::star_tower;
};

#endif
