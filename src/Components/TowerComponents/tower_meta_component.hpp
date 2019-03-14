#ifndef TOWER_META_COMPONENT_H
#define TOWER_META_COMPONENT_H

#include "Utility/utility.hpp"
#include "../base_component.hpp"

class TowerMetaComponent : public BaseComponent {
public:
  TowerMetaComponent(int _buildCost, int _sellGet, int _upgradeCost);

  static const int typeID = ComponentType::tower_meta;
  inline virtual int getTypeID() const { return typeID; };

  int buildCost;
  int sellGet;
  int upgradeCost;

private:
};

#endif