#ifndef COLLISION_COMPONENT_H
#define COLLISION_COMPONENT_H

#include "Utility/utility.hpp"
#include "base_component.hpp"
#include "entity.hpp"

namespace CollisionTypeID {
	enum CollisionTypeID {
		aabb_collision,
		mesh_collision
	};
}

class CollisionComponent : public BaseComponent
{
public:
	vec2 position;
	vec2 size;
	GLfloat rotation;
  CollisionComponent(vec2 _position, vec2 _size, GLfloat _rotation);
  CollisionComponent(vec2 _position, float _scale, GLfloat _rotation);
	virtual bool isCollidingWith(CollisionComponent &other);
	static const int typeID = ComponentType::collision;
	inline virtual int getTypeID() const { return typeID; };
	virtual int getCollisionType() { return CollisionTypeID::aabb_collision; };
};

#endif
