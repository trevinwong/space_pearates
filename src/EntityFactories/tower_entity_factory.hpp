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
#include "Components/TowerComponents/water_tower_attack_component.hpp"
#include "Components/TowerComponents/light_tower_attack_component.hpp"
#include "Components/TowerComponents/star_tower_attack_component.hpp"
#include "Components/TowerComponents/boomerang_tower_attack_component.hpp"
#include "Components/TowerComponents/tower_range_sprite_component.hpp"

class TowerEntityFactory
{
  public:
    // platformerGroundPosition is the center bottom position of a tower
    // Create a tower base on the given plaformer position
    // Tower should not be rotated, _rotate is always zero
    static Entity createFireTower(vec2 towerCenterBottomPosition, vec2 _size=vec2(40.0f, 65.0f));
    static Entity createWaterTower(vec2 towerCenterBottomPosition, vec2 _size=vec2(40.0f, 65.0f));
    static Entity createLightTower(vec2 towerCenterBottomPosition, vec2 _size=vec2(40.0f, 65.0f));
    static Entity createStarTower(vec2 towerCenterBottomPosition, vec2 _size=vec2(40.0f, 65.0f));
    static Entity createBoomerangTower(vec2 towerCenterBottomPosition, vec2 _size=vec2(40.0f, 65.0f));
  private:
    // factory class does not need instantiation
    TowerEntityFactory();
    static vec2 getTopLeftPosition(vec2 centerBottom, vec2 size);
};
#endif