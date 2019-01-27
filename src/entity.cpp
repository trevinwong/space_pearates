#include "entity.hpp"

Entity::Entity()
{
	// MAX_COMPONENTS is defined in component.hpp.
	// Please increment it every time you add a new component.
	components = std::vector<Component*>(MAX_COMPONENTS, nullptr);
}

