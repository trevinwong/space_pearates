#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "utility.hpp"
#include "Components/base_component.hpp"
#include "Components/projectile_component.hpp"
#include "entity.hpp"

/*
 * This class manages the global vector of entities on which systems act upon.
 */
class EntityManager {
public:
  bitset<ComponentType::max_count> getComponentChecker(ComponentType::ComponentType type);
  bitset<ComponentType::max_count> getComponentChecker(vector<int> components);
	shared_ptr<Entity> getEntityById(int id);
	vector<shared_ptr<Entity>> getEntities();
  vector<shared_ptr<Entity>> getEntities(bitset<ComponentType::max_count> component_checker);
  vector<shared_ptr<Entity>> getEntitiesHasOneOf(bitset<ComponentType::max_count> component_checker);
  vector<shared_ptr<Entity>> getEntitiesHasAllOf(bitset<ComponentType::max_count> component_checker);
	void addEntity(Entity e);
  bool removeEntity(shared_ptr<Entity> entity);

  // Remove entities that do NOT contain one of these component types
  void filterRemoveByComponentType(ComponentType::ComponentType type);
  void filterRemoveByComponentType(vector<int> components);

  void destroyAll();
private:
	vector<shared_ptr<Entity>> entities;
};

#endif
