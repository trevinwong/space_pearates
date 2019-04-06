#ifndef STATE_SYSTEM_H
#define STATE_SYSTEM_H

#include "Utility/utility.hpp"
#include "entity_manager.hpp"
#include "entity.hpp"
#include "Components/player_component.hpp"
#include "Components/transform_component.hpp"
#include "Components/collision_component.hpp"
#include "Components/color_component.hpp"
#include "Components/sprite_component.hpp"

class StateSystem
{
public:
  void handleStateChanges(EntityManager &entityManager, float dt);
  void handlePlayerState(shared_ptr<Entity> player, float dt);
};

#endif
