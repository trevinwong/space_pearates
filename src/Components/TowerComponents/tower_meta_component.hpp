#ifndef TOWER_META_COMPONENT_H
#define TOWER_META_COMPONENT_H

#include "utility.hpp"
#include "../base_component.hpp"

class TowerMetaComponent : public BaseComponent {
public:
  TowerMetaComponent(int _buildCost, int _sellGet);

  static const int typeID = ComponentType::tower_meta;
  inline virtual int getTypeID() const { return typeID; };

  int buildCost;
  int sellGet;
  // TODO: upgrade cost, e.g.
  // vector<int> upgradeCost = {0, 2, 3, 4} <= lvl0->1 needs 2

private:
};

#endif