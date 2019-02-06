#include "entity.hpp"

int Entity::next_id = 0;

Entity::Entity()
{
	id = next();
	components = std::vector<BaseComponent*>(ComponentType::max_count, nullptr);
}

