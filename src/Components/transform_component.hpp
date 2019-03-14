#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "Utility/utility.hpp"
#include "base_component.hpp"

class TransformComponent : public BaseComponent
{
public:
	TransformComponent(vec2 _position, vec2 _size, GLfloat _rotation);
  TransformComponent(vec2 _position, float _scale, GLfloat _rotation);
	vec2 position;
	vec2 size;
	GLfloat rotation;

	bool isCollidingWith(TransformComponent other);
	static const int typeID = ComponentType::transform;
	inline virtual int getTypeID() const { return typeID; };
};

#endif
