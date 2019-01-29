#ifndef SPRITE_SYSTEM_H
#define SPRITE_SYSTEM_H

#include "utility.hpp"
#include "texture.hpp"
#include "program.hpp"
#include "entity.hpp"
#include "sprite_component.hpp"
#include "transform_component.hpp"
#include "color_component.hpp"

class SpriteSystem
{
public:
	SpriteSystem();
	~SpriteSystem();
	// Iterates through all entities. If they have a Sprite, Transform and Color component, they are rendered.
	void drawSprites(std::vector<Entity> &entities, glm::mat4 projection);
};

#endif


