#ifndef TOWER_META_COMPONENT_H
#define TOWER_META_COMPONENT_H

#include "Utility/utility.hpp"
#include "../base_component.hpp"

class TowerMetaComponent : public BaseComponent {
public:
  TowerMetaComponent(int _buildCost, vector<int> _upgradeCostsPerLvl, int _maxLevel);

  static const int typeID = ComponentType::tower_meta;
  inline virtual int getTypeID() const { return typeID; };

  int buildCost;
  vector<int> upgradeCostsPerLvl;
  int totalWorth;
  int currentLevel;
  int maxLevel;

  int getSellMoney();

private:
  float SELLBACK_RATIO = 0.5;
};

#endif
