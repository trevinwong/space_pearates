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

shared_ptr<Entity> EntityManager::getEntityById(int _id) {
  shared_ptr<Entity> target = nullptr;
  for (shared_ptr<Entity> e : entities) {
    if (e->id == _id) {
      target = e;
      break;
    }
  }
  return target;
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

vector<shared_ptr<Entity>> EntityManager::getEntitiesHasAllOf(bitset<ComponentType::max_count> component_checker)
{
  vector<shared_ptr<Entity>> filtered_entities;
  for (shared_ptr<Entity> e : entities) {
    if (e->hasAllOfComponents(component_checker)) {
      filtered_entities.push_back(e);
    }
  }
  return filtered_entities;
}

void EntityManager::addEntity(Entity e)
{
  entities.push_back(make_shared<Entity>(e));
}

void EntityManager::addEntity(shared_ptr<Entity> e)
{
  entities.push_back(e);
}

bool EntityManager::removeEntity(shared_ptr<Entity> entity) {
  for (int i = 0; i < entities.size(); i++) {
    shared_ptr<Entity> e = entities[i];
    if (e == entity) {
      entities[i] = entities.back();
      entities.pop_back();
      return true;
    }
  }
  return false;
}

int EntityManager::getSize()
{
  return entities.size();
}

void EntityManager::filterRemoveByComponentType(ComponentType::ComponentType type)
{
  filterRemoveByComponentType(vector<int>{type});
}

void EntityManager::filterRemoveByComponentType(vector<int> types)
{
  for (int i = entities.size()-1; i >= 0; i--) {
    shared_ptr<Entity> e = entities[i];
    if (e->hasNoneOfComponents(getComponentChecker(types))) {
      entities[i] = entities.back();
      entities.pop_back();
    }
  }
}
