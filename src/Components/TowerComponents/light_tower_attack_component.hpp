#ifndef LIGHT_TOWER_ATTACK_COMPONENT_H
#define LIGHT_TOWER_ATTACK_COMPONENT_H

#include "Utility/utility.hpp"
#include "../base_component.hpp"
#include "fire_tower_attack_component.hpp"

class LightTowerAttackComponent : public TowerAttackComponent {
public:
  LightTowerAttackComponent(vec2 _relativeFirePosition, vector<int> _attackPerLvl, vector<float> _rangePerLvl, vector<float> _fireRatePerLvl, vector<int> _numProjectilesPerLvl);

  int getProjectileNumberPerShoot();
  vector<int> numProjectilesPerLvl;
  int projectileNumberPerShoot;

  virtual void setToLevel(int level);
  virtual int getTowerType() { return towerTypeID; };
    virtual shared_ptr<Texture> getLevelTexture(int level);


private:
  static const int towerTypeID = TowerTypeID::light_tower;
};

#endif
