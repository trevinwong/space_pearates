#ifndef COLLISION_COMPONENT_H
#define COLLISION_COMPONENT_H

#include "Utility/utility.hpp"
#include "base_component.hpp"
#include "entity.hpp"

class CollisionComponent : public BaseComponent
{
public:
	vec2 position;
	vec2 size;
	GLfloat rotation;
  CollisionComponent(vec2 _position, vec2 _size, GLfloat _rotation);
  CollisionComponent(vec2 _position, float _scale, GLfloat _rotation);
	bool isCollidingWith(CollisionComponent other);
	static const int typeID = ComponentType::collision;
	inline virtual int getTypeID() const { return typeID; };
};

#endif
