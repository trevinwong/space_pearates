#ifndef TOWER_H
#define TOWER_H

#include <vector>
#include "utility.hpp"
#include "entity.hpp"
#include "entity_manager.hpp"
#include "Systems/sprite_system.hpp"
#include "Components/health_component.hpp"
#include "Components/TowerComponents/tower_meta_component.hpp"
#include "Components/TowerComponents/fire_tower_attack_component.hpp"
#include "Components/TowerComponents/fire_tower_range_sprite_component.hpp"
#include "Components/TowerComponents/light_tower_attack_component.hpp"
#include "Components/TowerComponents/light_tower_range_sprite_component.hpp"

class TowerEntityFactory
{
  public:
    // platformerGroundPosition is the center bottom position of a tower
    // Create a tower base on the given plaformer position
    // Tower should not be rotated, _rotate is always zero
    static Entity createFireTower(glm::vec2 towerCenterBottomPosition, glm::vec2 _size);
    static Entity createLightTower(glm::vec2 towerCenterBottomPosition, glm::vec2 _size);
  private:
    // factory class does not need instantiation
    TowerEntityFactory();
};
#endif