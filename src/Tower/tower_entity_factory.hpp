#ifndef TOWER_H
#define TOWER_H

#include <vector>
#include "utility.hpp"
#include "entity.hpp"
#include "entity_manager.hpp"
#include "sprite_system.hpp"

class TowerEntityFactory
{
  public:
    // platformerGroundPosition is the center bottom position of a tower
    // Create a tower base on the given plaformer position
    // Tower should not be rotated, _rotate is always zero
    static Entity createTower(glm::vec2 towerCenterBottomPosition, glm::vec2 _size);
  private:
    // factory class does not need instantiation
    TowerEntityFactory();
};
#endif