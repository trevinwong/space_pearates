#ifndef PLAYER_FACTORY_H
#define PLAYER_FACTORY_H

#include "entity.hpp"
#include "Utility/program.hpp"
#include "Components/sprite_component.hpp"
#include "Components/transform_component.hpp"
#include "Components/color_component.hpp"
#include "Components/player_component.hpp"
#include "Components/movement_component.hpp"
#include "Components/collision_component.hpp"
#include "Components/animated_component.hpp"
#include "Components/wallet_component.hpp"
#include "Components/health_component.hpp"
#include "Components/collision_component.hpp"
#include "DataLoaders/player_data_loader.hpp"
#include "DataLoaders/player_structs.hpp"


class PlayerFactory
{
public:
  static Entity build(vec2 translation);
};

#endif
