#ifndef PLAYER_SYSTEM_H
#define PLAYER_SYSTEM_H

#include "Utility/utility.hpp"
#include "entity.hpp"
#include "entity_manager.hpp"
#include "Utility/audio_loader.hpp"
#include "Components/player_component.hpp"
#include "Components/movement_component.hpp"
#include "Components/sprite_component.hpp"
#include "Components/transform_component.hpp"
#include "Components/color_component.hpp"
#include "Components/collision_component.hpp"

class PlayerSystem
{
public:	
	void interpInput(EntityManager &entityManager, float dt, GLboolean keys[], GLboolean keysProcessed[]);
  void handleActionsInNeutral(shared_ptr<Entity> player, float dt, GLboolean keys[], GLboolean keysProcessed[]);
  void handleActionsInHitstun(shared_ptr<Entity> player, float dt, GLboolean keys[], GLboolean keysProcessed[]);
};

#endif
