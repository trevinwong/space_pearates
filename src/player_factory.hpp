#ifndef PLAYER_FACTORY_H
#define PLAYER_FACTORY_H

#include "entity.hpp"
#include "program.hpp"
#include "sprite_component.hpp"
#include "transform_component.hpp"
#include "color_component.hpp"
#include "player_component.hpp"
#include "movement_component.hpp"

class PlayerFactory
{
public:
	PlayerFactory();
	~PlayerFactory();
	Entity build();
};

#endif