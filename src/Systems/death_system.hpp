#ifndef DEATH_SYSTEM_H
#define DEATH_SYSTEM_H

#include "utility.hpp"
#include "entity_manager.hpp"
#include "entity.hpp"
#include "Components/death_component.hpp"
#include "Components/transform_component.hpp"
#include "Components/enemy_component.hpp"
#include "Components/projectile_component.hpp"
#include "EntityFactories/resource_factory.hpp"
#include "Systems/waveset_system.hpp"
#include "Systems/particle_system.hpp"
#include "audio_loader.hpp"


class DeathSystem
{
public:
  void handleDeaths(EntityManager &entityManager);
};

#endif
