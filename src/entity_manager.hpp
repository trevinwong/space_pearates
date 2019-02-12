#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "utility.hpp"
#include "Components/base_component.hpp"
#include "entity.hpp"

/*
 * This class manages the global vector of entities on which systems act upon.
 */
class EntityManager {
public:
	void addEntity(Entity e);
	bitset<ComponentType::max_count> getComponentChecker(vector<int> components);
	vector<shared_ptr<Entity>> getEntities();
  vector<shared_ptr<Entity>> getEntities(bitset<ComponentType::max_count> component_checker);
  vector<shared_ptr<Entity>> getEntitiesHasOneOf(bitset<ComponentType::max_count> component_checker);
  bool removeEntity(shared_ptr<Entity> entity);
private:
	vector<shared_ptr<Entity>> entities;
};

#endif
