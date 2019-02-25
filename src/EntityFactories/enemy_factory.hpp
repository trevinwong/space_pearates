#ifndef ENEMY_FACTORY_H
#define ENEMY_FACTORY_H

#include "entity.hpp"
#include "program.hpp"
#include "Components/sprite_component.hpp"
#include "Components/transform_component.hpp"
#include "Components/color_component.hpp"
#include "Components/movement_component.hpp"
#include "Components/health_component.hpp"
#include "Components/enemy_component.hpp"
#include "Components/enemy_spawn_component.hpp"
#include "Components/collision_component.hpp"

class EnemyFactory
{
public:
  static Entity build(vec2 position, vec2 velocity, vec2 scale=vec2(40.0f,40.0f));
};

#endif
