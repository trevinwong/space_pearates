#include "boomerang_tower_attack_component.hpp"

BoomerangTowerAttackComponent::BoomerangTowerAttackComponent(vec2 _relativeFirePosition, vector<int> _attackPerLvl, vector<float> _rangePerLvl, vector<float> _fireRatePerLvl) :
  TowerAttackComponent(_relativeFirePosition, _attackPerLvl, _rangePerLvl, _fireRatePerLvl)
{
  setToLevel(0);
}

shared_ptr<Texture> BoomerangTowerAttackComponent::getLevelTexture(int level) {
  shared_ptr<BoomerangTowerData> data = std::dynamic_pointer_cast<BoomerangTowerData>(TowerDataLoader::allTowerData[BUILD_BOOMERANG_TOWER]);
  return data->towerTextures[level];
}

void BoomerangTowerAttackComponent::setToLevel(int level)
{
  attackRange = rangePerLvl[level];
  fireRate = fireRatePerLvl[level];
  projectileAttackPower = attackPerLvl[level]; 
}
