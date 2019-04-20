#include "star_tower_attack_component.hpp"

StarTowerAttackComponent::StarTowerAttackComponent(vec2 _relativeFirePosition, vector<int> _attackPerLvl, vector<float> _rangePerLvl, vector<float> _fireRatePerLvl, vector<float> _sizePerLvl) :
  TowerAttackComponent(_relativeFirePosition, _attackPerLvl, _rangePerLvl, _fireRatePerLvl),
  sizePerLvl(_sizePerLvl)
{
  setToLevel(0);
}

shared_ptr<Texture> StarTowerAttackComponent::getLevelTexture(int level) {
  shared_ptr<StarTowerData> data = std::dynamic_pointer_cast<StarTowerData>(TowerDataLoader::allTowerData[BUILD_STAR_TOWER]);
  return data->towerTextures[level];
}

void StarTowerAttackComponent::setToLevel(int level)
{
  attackRange = rangePerLvl[level];
  fireRate = fireRatePerLvl[level];
  projectileAttackPower = attackPerLvl[level]; 
  projectileSize = vec2(sizePerLvl[level], sizePerLvl[level]);
}

vec2 StarTowerAttackComponent::getProjectileSize()
{
  return projectileSize * SCALING_FACTOR;
}
