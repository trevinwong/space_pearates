#include "water_tower_attack_component.hpp"

WaterTowerAttackComponent::WaterTowerAttackComponent(vec2 _relativeFirePosition, vector<float> _rangePerLvl, vector<float> _slowPerLvl) :
  TowerAttackComponent(_relativeFirePosition, vector<int>{}, _rangePerLvl, vector<float>{}),
  slowPerLvl(_slowPerLvl)
{
  setToLevel(0);
  shared_ptr<Texture> lvl1_texture = make_shared<Texture>(texture_path("water_tower.png"), true);
  shared_ptr<Texture> lvl2_texture = make_shared<Texture>(texture_path("water_tower2.png"), true);
  shared_ptr<Texture> lvl3_texture = make_shared<Texture>(texture_path("water_tower3.png"), true);
  shared_ptr<Texture> lvl4_texture = make_shared<Texture>(texture_path("water_tower4.png"), true);
  towerTextures.push_back(lvl1_texture);
  towerTextures.push_back(lvl2_texture);
  towerTextures.push_back(lvl3_texture);
  towerTextures.push_back(lvl4_texture);
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
