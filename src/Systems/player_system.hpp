#ifndef PLAYER_SYSTEM_H
#define PLAYER_SYSTEM_H

#include "utility.hpp"
#include "entity.hpp"
#include "entity_manager.hpp"
#include "Components/player_component.hpp"
#include "Components/movement_component.hpp"

class PlayerSystem
{
public:	
	void interpInput(EntityManager &entityManager, float dt, GLboolean keys[], GLboolean keysProcessed[]);
};

#endif
