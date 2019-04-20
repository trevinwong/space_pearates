#include "light_tower_attack_component.hpp"

LightTowerAttackComponent::LightTowerAttackComponent(vec2 _relativeFirePosition, vector<int> _attackPerLvl, vector<float> _rangePerLvl, vector<float> _fireRatePerLvl, vector<int> _numProjectilesPerLvl) :
  TowerAttackComponent(_relativeFirePosition, _attackPerLvl, _rangePerLvl, _fireRatePerLvl),
  numProjectilesPerLvl(_numProjectilesPerLvl)
{
  setToLevel(0);
  shared_ptr<Texture> lvl1_texture = make_shared<Texture>(texture_path("towers/light_tower.png"), true);
  shared_ptr<Texture> lvl2_texture = make_shared<Texture>(texture_path("towers/light_tower2.png"), true);
  shared_ptr<Texture> lvl3_texture = make_shared<Texture>(texture_path("towers/light_tower3.png"), true);
  shared_ptr<Texture> lvl4_texture = make_shared<Texture>(texture_path("towers/light_tower4.png"), true);
  towerTextures.push_back(lvl1_texture);
  towerTextures.push_back(lvl2_texture);
  towerTextures.push_back(lvl3_texture);
  towerTextures.push_back(lvl4_texture);
}

void LightTowerAttackComponent::setToLevel(int level)
{
  attackRange = rangePerLvl[level];
  fireRate = fireRatePerLvl[level];
  projectileAttackPower = attackPerLvl[level]; 
  projectileNumberPerShoot = numProjectilesPerLvl[level];
}

int LightTowerAttackComponent::getProjectileNumberPerShoot()
{
  return this->projectileNumberPerShoot;
}
