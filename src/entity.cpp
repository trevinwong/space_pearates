#include "entity.hpp"

int Entity::next_id = 0;

Entity::Entity()
{
	// MAX_COMPONENTS is defined in component.hpp.
	// Please increment it every time you add a new component.
	id = next();
	std::cout << id << std::endl;
	components = std::vector<BaseComponent*>(MAX_COMPONENTS, nullptr);
}

