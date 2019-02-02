#ifndef COLLISION_COMPONENT_H
#define COLLISION_COMPONENT_H

#include "utility.hpp"
#include "component.hpp"
#include <vector>
#include "entity.hpp"

class CollisionComponent : public BaseComponent
{
public:

    // Position, size, and rotation of collision box
	CollisionComponent(glm::vec2 _position, glm::vec2 _size, GLfloat _rotate);
	~CollisionComponent();
    
    bool hasCollided;

    // Entity may collide with multiple objects at once
    std::vector<Entity> entities;

    // Position, size, and rotation of collision box
    glm::vec2 position;
		glm::vec2 size;
		GLfloat   rotate;

	static const int typeID = COLLISION_COMPONENT_TYPEID;
	inline virtual int getTypeID() const { return typeID; };
};

#endif
