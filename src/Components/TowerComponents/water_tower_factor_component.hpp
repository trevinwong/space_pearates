#ifndef WATER_TOWER_FACTOR_COMPONENT_H
#define WATER_TOWER_FACTOR_COMPONENT_H

#include "../base_component.hpp"

/*
  Every entity which has this component will be influenced by the water tower
  e.g. slow down if is in the water tower range
*/
class WaterTowerFactorComponent : public BaseComponent {
  public:
    WaterTowerFactorComponent() : speedFactor(1.0f){};
    float speedFactor;

    static const int typeID = ComponentType::water_tower_factor;
    virtual int getTypeID() const { return typeID; };
};

#endif // !WATER_TOWER_FACTOR_COMPONENT_H
