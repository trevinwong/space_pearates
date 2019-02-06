#ifndef COLLISION_COMPONENT_H
#define COLLISION_COMPONENT_H

#include "utility.hpp"
#include "base_component.hpp"
#include "entity.hpp"
#include <vector>

class CollisionComponent : public BaseComponent
{
public:
  CollisionComponent(glm::vec2 _position, glm::vec2 _size, GLfloat _rotate);
	glm::vec2 position;
	glm::vec2 size;
	GLfloat   rotate;
	static const int typeID = ComponentType::collision;
	inline virtual int getTypeID() const { return typeID; };
};

#endif
