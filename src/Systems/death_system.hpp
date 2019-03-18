#ifndef DEATH_SYSTEM_H
#define DEATH_SYSTEM_H

#include "Utility/utility.hpp"
#include "entity_manager.hpp"
#include "entity.hpp"
#include "Components/death_component.hpp"
#include "Components/transform_component.hpp"
#include "Components/enemy_component.hpp"
#include "Components/projectile_component.hpp"
#include "Components/player_component.hpp"
#include "hud.hpp"
#include "EntityFactories/resource_factory.hpp"
#include "Systems/waveset_system.hpp"
#include "Systems/particle_system.hpp"
#include "Utility/audio_loader.hpp"


class DeathSystem
{
public:
	void handleEnemyDeath(EntityManager &entityManager, shared_ptr<Entity> enemy);
	void handleProjectileDeath(EntityManager &entityManager, shared_ptr<Entity> projectile);
	void handlePlayerDeath(EntityManager &entityManager, shared_ptr<Entity> player);
  void handleDeaths(EntityManager &entityManager);
  int dropRate = 50;
};

#endif
