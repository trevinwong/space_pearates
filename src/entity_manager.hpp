#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "utility.hpp"
#include "entity.hpp"

/*
 * This class manages the global vector of entities on which systems act upon.
 */
class EntityManager {
public:
	EntityManager();
	~EntityManager();
	void addEntity(Entity e);
	vector<shared_ptr<Entity>> getEntities();
private:
	vector<shared_ptr<Entity>> entities;
};

#endif
