#ifndef DAMAGE_SYSTEM_H
#define DAMAGE_SYSTEM_H

#include "Utility/utility.hpp"
#include "entity_manager.hpp"
#include "entity.hpp"
#include "Components/damage_component.hpp"
#include "Components/player_component.hpp"
#include "Components/home_component.hpp"
#include "Components/death_component.hpp"
#include "Components/health_component.hpp"
#include "EntityFactories/resource_factory.hpp"
#include "hud.hpp"



class DamageSystem
{
public:
  void handleDamage(EntityManager &entityManager);
};

#endif
