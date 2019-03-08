#ifndef TOWER_SHOOTING_SYSTEM_H
#define TOWER_SHOOTING_SYSTEM_H

#include "utility.hpp"
#include "entity.hpp"
#include "Components/sprite_component.hpp"
#include "Components/movement_component.hpp"
#include "Components/collision_component.hpp"
#include "Components/transform_component.hpp"
#include "Components/TowerComponents/fire_tower_attack_component.hpp"
#include "Components/TowerComponents/water_tower_attack_component.hpp"
#include "Components/TowerComponents/water_tower_factor_component.hpp"
#include "Components/TowerComponents/light_tower_attack_component.hpp"
#include "Components/TowerComponents/star_tower_attack_component.hpp"
#include "../entity_manager.hpp"
#include "../EntityFactories/projectile_entity_factory.hpp"

/*
  check if any enemy is in the range of a tower
  create projectile and shoot the projectile to the enemy
*/
class TowerAttackSystem {
  public:
    void checkRangeAndShootProjectiles(EntityManager& entityManager);
    void reduceElapsedTimeToNextFire(EntityManager& entityManager, float dt);
};

#endif