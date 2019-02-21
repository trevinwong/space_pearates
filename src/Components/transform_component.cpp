#include "transform_component.hpp"

TransformComponent::TransformComponent(glm::vec2 _position, glm::vec2 _size, GLfloat _rotation) : 
	position(_position), size(_size), rotation(_rotation)
{
}

bool TransformComponent::isCollidingWith(TransformComponent other)
{	
	bool overlapX = position.x + size.x >= other.position.x
		&& other.position.x + other.size.x >= position.x;

	bool overlapY = position.y + size.y >= other.position.y
	&& other.position.y + other.size.y >= position.y;

	return overlapX && overlapY;
}
