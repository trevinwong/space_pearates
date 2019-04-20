#include "water_tower_attack_component.hpp"

WaterTowerAttackComponent::WaterTowerAttackComponent(vec2 _relativeFirePosition, vector<float> _rangePerLvl, vector<float> _slowPerLvl) :
  TowerAttackComponent(_relativeFirePosition, vector<int>{}, _rangePerLvl, vector<float>{}),
  slowPerLvl(_slowPerLvl)
{
  setToLevel(0);
}

shared_ptr<Texture> WaterTowerAttackComponent::getLevelTexture(int level) {
  shared_ptr<WaterTowerData> data = std::dynamic_pointer_cast<WaterTowerData>(TowerDataLoader::allTowerData[BUILD_WATER_TOWER]);
  return data->towerTextures[level];
}

void WaterTowerAttackComponent::setToLevel(int level)
{
  attackRange = rangePerLvl[level];
  slowDownFactor = slowPerLvl[level]; 
}

float WaterTowerAttackComponent::getSlowDownFactor()
{
  return (1 - slowDownFactor / 100);
}
