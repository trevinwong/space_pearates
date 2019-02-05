#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H

// TODO: Remove unneeded includes
#include "utility.hpp"
#include "texture.hpp"
#include "program.hpp"
#include "entity.hpp"
#include "Components/sprite_component.hpp"
#include "Components/transform_component.hpp"
#include "Components/movement_component.hpp"

class MovementSystem
{
public:
	MovementSystem();
	~MovementSystem();
	// Iterates through all entities. If they have a Movement component, they are translated based on the
	// information in the component.
	void moveEntities(std::vector<Entity> &entities);
};

#endif


