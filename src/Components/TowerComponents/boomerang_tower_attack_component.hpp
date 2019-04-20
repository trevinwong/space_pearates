#ifndef BOOMERANG_TOWER_ATTACK_COMPONENT_H
#define BOOMERANG_TOWER_ATTACK_COMPONENT_H

#include "Utility/utility.hpp"
#include "../base_component.hpp"
#include "tower_attack_component.hpp"
#include <DataLoaders/tower_data_loader.hpp>

class BoomerangTowerAttackComponent : public TowerAttackComponent {
public:
  BoomerangTowerAttackComponent(vec2 _relativeFirePosition, vector<int> _attackPerLvl, vector<float> _rangePerLvl, vector<float> _fireRatePerLvl);

  virtual void setToLevel(int level);
  virtual int getTowerType() { return towerTypeID; };
    virtual shared_ptr<Texture> getLevelTexture(int level);

private:
  static const int towerTypeID = TowerTypeID::boomerang_tower;
};

#endif
