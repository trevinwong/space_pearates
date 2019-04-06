#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include "Utility/utility.hpp"
#include "base_component.hpp"
#include "Utility/program.hpp"
#include "Utility/texture.hpp"
#include "Utility/timer.hpp"

class SpriteComponent : public BaseComponent
{
public:
	SpriteComponent(shared_ptr<Program> _program, shared_ptr<Texture> _texture);
	~SpriteComponent();
	static const int typeID = ComponentType::sprite;
	inline virtual int getTypeID() const { return typeID; };
  Timer blinkTimer;
	shared_ptr<Program> program;
	shared_ptr<Texture> texture;
	GLuint VBO; // We want to create a square in which we can overlay our texture on.
	GLuint quadVAO; // we only need VAO as a member as it remembers any VBOs it's associated with
};

#endif
