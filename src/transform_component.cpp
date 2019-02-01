#include "transform_component.hpp"

TransformComponent::TransformComponent(glm::vec2 _position, glm::vec2 _size, GLfloat _rotate) : 
	position(_position), size(_size), rotate(_rotate)
{
}

TransformComponent::~TransformComponent()
{
}
