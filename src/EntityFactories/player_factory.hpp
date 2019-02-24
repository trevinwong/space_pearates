#ifndef PLAYER_FACTORY_H
#define PLAYER_FACTORY_H

#include "entity.hpp"
#include "program.hpp"
#include "Components/sprite_component.hpp"
#include "Components/transform_component.hpp"
#include "Components/color_component.hpp"
#include "Components/player_component.hpp"
#include "Components/movement_component.hpp"
#include "Components/collision_component.hpp"
#include "Components/animated_component.hpp"
#include "Components/wallet_component.hpp"

class PlayerFactory
{
public:
  static Entity build(vec2 translation, vec2 scale);
};

#endif
