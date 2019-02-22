#ifndef TOWER_META_COMPONENT_H
#define TOWER_META_COMPONENT_H

#include "utility.hpp"
#include "../base_component.hpp"

class TowerMetaComponent : public BaseComponent {
public:
  TowerMetaComponent();
  ~TowerMetaComponent();

  static const int typeID = ComponentType::tower_meta;
  inline virtual int getTypeID() const { return typeID; };

private:
};

#endif