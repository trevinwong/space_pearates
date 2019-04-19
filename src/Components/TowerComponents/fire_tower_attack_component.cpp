#include "fire_tower_attack_component.hpp"

FireTowerAttackComponent::FireTowerAttackComponent(vec2 _relativeFirePosition, vector<int> _attackPerLvl, vector<float> _rangePerLvl, vector<float> _fireRatePerLvl) :
  TowerAttackComponent(_relativeFirePosition, _attackPerLvl, _rangePerLvl, _fireRatePerLvl)
{
  setToLevel(0);
  shared_ptr<Texture> lvl1_texture = make_shared<Texture>(texture_path("fire_tower.png"), true);
  shared_ptr<Texture> lvl2_texture = make_shared<Texture>(texture_path("fire_tower2.png"), true);
  shared_ptr<Texture> lvl3_texture = make_shared<Texture>(texture_path("fire_tower3.png"), true);
  shared_ptr<Texture> lvl4_texture = make_shared<Texture>(texture_path("fire_tower4.png"), true);
  shared_ptr<Texture> lvl5_texture = make_shared<Texture>(texture_path("fire_tower5.png"), true);
  shared_ptr<Texture> lvl6_texture = make_shared<Texture>(texture_path("fire_tower6.png"), true);
  towerTextures.push_back(lvl1_texture);
  towerTextures.push_back(lvl2_texture);
  towerTextures.push_back(lvl3_texture);
  towerTextures.push_back(lvl4_texture);
  towerTextures.push_back(lvl5_texture);
  towerTextures.push_back(lvl6_texture);
}

void FireTowerAttackComponent::setToLevel(int level)
{
  attackRange = rangePerLvl[level];
  fireRate = fireRatePerLvl[level];
  projectileAttackPower = attackPerLvl[level]; 
}
