#include "tower_meta_component.hpp"

TowerMetaComponent::TowerMetaComponent(int _buildCost, vector<int>_upgradeCostsPerLvl, int _maxLevel):
  buildCost(_buildCost), upgradeCostsPerLvl(_upgradeCostsPerLvl), maxLevel(_maxLevel)
{
  totalWorth = buildCost;
  currentLevel = 0;
}

int TowerMetaComponent::getSellMoney()
{
  return totalWorth * 0.5;
}
