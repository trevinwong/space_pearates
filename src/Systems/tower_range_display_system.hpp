#ifndef TOWER_RANGE_DISPLAY_SYSTEM_H
#define TOWER_RANGE_DISPLAY_SYSTEM_H

#include "utility.hpp"
#include "texture.hpp"
#include "program.hpp"
#include "entity.hpp"
#include "entity_manager.hpp"
#include "../Components/sprite_component.hpp"
#include "../Components/transform_component.hpp"
#include "../Components/map_component.hpp"
#include "../Components/TowerComponents/fire_tower_attack_component.hpp"
#include "../Components/TowerComponents/light_tower_attack_component.hpp"
#include "../Components/TowerComponents/tower_range_sprite_component.hpp"

class TowerRangeDisplaySystem
{
public:
  TowerRangeDisplaySystem();
  ~TowerRangeDisplaySystem();

  void drawRanges(EntityManager &entityManager, glm::mat4 projection);

private:
  void drawRangesHelper(SpriteComponent *towerRangeSpriteComponent, glm::vec2 shootRangeCircleCenterPosition, float towerRadius, glm::mat4 projection);
};

#endif