#include "entity_manager.hpp"

bitset<ComponentType::max_count> EntityManager::getComponentChecker(ComponentType::ComponentType type)
{
  return getComponentChecker(vector<int>{type});
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

void EntityManager::addEntity(Entity e)
{
  entities.push_back(make_shared<Entity>(e));
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

void EntityManager::filterRemoveByComponentType(ComponentType::ComponentType type)
{
  filterRemoveByComponentType(vector<int>{type});
}

void EntityManager::filterRemoveByComponentType(vector<int> types)
{
  for (int i = 0; i < entities.size(); i++) {
    shared_ptr<Entity> e = entities[i];
    if (e->hasNoneOfComponents(getComponentChecker(types))) {
      entities[i] = entities[entities.size() - 1];
      entities.pop_back();
    }
  }
}

void EntityManager::destroyAll()
{
  entities.clear();
}
