#include "entity_manager.hpp"

void EntityManager::addEntity(Entity e)
{
	entities.push_back(make_shared<Entity>(e));
}

bitset<ComponentType::max_count> EntityManager::getComponentChecker(vector<int> components)
{
  bitset<ComponentType::max_count> component_checker;
  for (int bit_pos : components) {
    component_checker.set(bit_pos, true);
  }
  return component_checker;	
}

vector<shared_ptr<Entity>> EntityManager::getEntities() {
	return entities;
}

vector<shared_ptr<Entity>> EntityManager::getEntities(bitset<ComponentType::max_count> component_checker)
{
	vector<shared_ptr<Entity>> filtered_entities;
	for (shared_ptr<Entity> e : entities) {
		if (e->hasComponents(component_checker)) {
			filtered_entities.push_back(e);
		}	
	}
	return filtered_entities;
}

vector<shared_ptr<Entity>> EntityManager::getEntitiesHasOneOf(bitset<ComponentType::max_count> component_checker)
{
  vector<shared_ptr<Entity>> filtered_entities;
  for (shared_ptr<Entity> e : entities) {
    if (e->hasOneOfComponents(component_checker)) {
      filtered_entities.push_back(e);
    }
  }
  return filtered_entities;
}

bool EntityManager::removeEntity(shared_ptr<Entity> entity) {
	for (int i = 0; i < entities.size(); i++) {	
		shared_ptr<Entity> e = entities[i];
		if (e == entity) {
			entities[i] = entities[entities.size() - 1];
			entities.pop_back();
			return true;
		}	
	}
  return false;
}
