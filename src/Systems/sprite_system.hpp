#ifndef SPRITE_SYSTEM_H
#define SPRITE_SYSTEM_H

#include "Utility/utility.hpp"
#include "Utility/texture.hpp"
#include "Utility/program.hpp"
#include "entity.hpp"
#include "entity_manager.hpp"
#include "Components/base_component.hpp"
#include "Components/sprite_component.hpp"
#include "Components/transform_component.hpp"
#include "Components/color_component.hpp"
#include "Components/collision_component.hpp"
#include "Components/animated_component.hpp"
#include "Components/player_component.hpp"
#include "Components/particle_component.hpp"

class SpriteSystem
{
public:
	void drawSprites(EntityManager &entityManager, glm::mat4 projection);
	void updateAnimatedSprites(EntityManager &entityManager);
};

#endif


