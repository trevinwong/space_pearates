#ifndef DEATH_SYSTEM_H
#define DEATH_SYSTEM_H

#include "utility.hpp"
#include "entity_manager.hpp"
#include "entity.hpp"
#include "Components/death_component.hpp"

class DeathSystem
{
public:
	void handleDeaths(EntityManager &entityManager);
};

#endif
