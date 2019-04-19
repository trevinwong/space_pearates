#include "star_tower_attack_component.hpp"

StarTowerAttackComponent::StarTowerAttackComponent(vec2 _relativeFirePosition, vector<int> _attackPerLvl, vector<float> _rangePerLvl, vector<float> _fireRatePerLvl, vector<float> _sizePerLvl) :
  TowerAttackComponent(_relativeFirePosition, _attackPerLvl, _rangePerLvl, _fireRatePerLvl),
  sizePerLvl(_sizePerLvl)
{
  setToLevel(0);
  shared_ptr<Texture> lvl1_texture = make_shared<Texture>(texture_path("star_tower.png"), true);
  shared_ptr<Texture> lvl2_texture = make_shared<Texture>(texture_path("star_tower2.png"), true);
  shared_ptr<Texture> lvl3_texture = make_shared<Texture>(texture_path("star_tower3.png"), true);
  shared_ptr<Texture> lvl4_texture = make_shared<Texture>(texture_path("star_tower4.png"), true);
  shared_ptr<Texture> lvl5_texture = make_shared<Texture>(texture_path("star_tower5.png"), true);
  towerTextures.push_back(lvl1_texture);
  towerTextures.push_back(lvl2_texture);
  towerTextures.push_back(lvl3_texture);
  towerTextures.push_back(lvl4_texture);
  towerTextures.push_back(lvl5_texture);
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
