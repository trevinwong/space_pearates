#ifndef SPRITE_SYSTEM_H
#define SPRITE_SYSTEM_H

#include "utility.hpp"
#include "texture.hpp"
#include "program.hpp"
#include "entity.hpp"
#include "Components/sprite_component.hpp"
#include "Components/transform_component.hpp"
#include "Components/color_component.hpp"
#include "Components/collision_component.hpp"

class SpriteSystem
{
public:
	SpriteSystem();
	~SpriteSystem();
	// Iterates through all entities. If they have a Sprite, Transform and Color component, they are rendered.
	void drawSprites(std::vector<Entity> &entities, glm::mat4 projection);
};

#endif


