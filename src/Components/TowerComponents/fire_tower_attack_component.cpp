#include "fire_tower_attack_component.hpp"

FireTowerAttackComponent::FireTowerAttackComponent(vec2 _relativeFirePosition, vector<int> _attackPerLvl, vector<float> _rangePerLvl, vector<float> _fireRatePerLvl) :
  TowerAttackComponent(_relativeFirePosition, _attackPerLvl, _rangePerLvl, _fireRatePerLvl)
{
  setToLevel(0);
}

shared_ptr<Texture> FireTowerAttackComponent::getLevelTexture(int level) {
  shared_ptr<FireTowerData> data = std::dynamic_pointer_cast<FireTowerData>(TowerDataLoader::allTowerData[BUILD_FIRE_TOWER]);
  return data->towerTextures[level];
}

void FireTowerAttackComponent::setToLevel(int level)
{
  attackRange = rangePerLvl[level];
  fireRate = fireRatePerLvl[level];
  projectileAttackPower = attackPerLvl[level]; 
}
