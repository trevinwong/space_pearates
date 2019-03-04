#include "entity.hpp"

int Entity::next_id = 0;

Entity::Entity()
{
	id = next();
	components = std::vector<BaseComponent*>(ComponentType::max_count, nullptr);
}

bool Entity::hasComponents(std::bitset<ComponentType::max_count> component_checker)
{
	return ((component_checker & has_components) == component_checker);
}

bool Entity::hasOneOfComponents(std::bitset<ComponentType::max_count> component_checker)
{
  return ((component_checker & has_components).any());
}

bool Entity::hasNoneOfComponents(std::bitset<ComponentType::max_count> component_checker)
{
  return ((component_checker & has_components).none());
}

void Entity::print()
{
	cout << "Entity ID: " << id << endl;
	for (BaseComponent* component : components) {
		if (component != nullptr) cout << component->getTypeID() << "  ";
	}
	cout << endl;
}
