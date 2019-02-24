#include "collision_component.hpp"

CollisionComponent::CollisionComponent(vec2 _position, vec2 _size, GLfloat _rotation) :
  position(_position), size(_size), rotation(_rotation)
{
}


bool CollisionComponent::isCollidingWith(CollisionComponent other)
{	
	bool overlapX = position.x + size.x >= other.position.x
		&& other.position.x + other.size.x >= position.x;

	bool overlapY = position.y + size.y >= other.position.y
	&& other.position.y + other.size.y >= position.y;

	return overlapX && overlapY;
}
