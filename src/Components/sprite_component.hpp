#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include "utility.hpp"
#include "base_component.hpp"
#include "program.hpp"
#include "texture.hpp"

class SpriteComponent : public BaseComponent
{
public:
	SpriteComponent(Program *_program, Texture *_texture);
	~SpriteComponent();
	static const int typeID = ComponentType::sprite;
	inline virtual int getTypeID() const { return typeID; };
	Program *program;
	Texture *texture;
	GLuint  quadVAO; // we only need VAO as a member as it remembers any VBOs it's associated with
};

#endif
