#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "utility.hpp"
#include "entity.hpp"

/*
 * This class manages the global vector of entities on which systems act upon.
 * In the future, this EntityManager class can be extended to use a bitmask to return a list of entities that match the system's needs for performance reasons.
 * However, we're keeping it simple for now and simply returning all entities to a system and letting them check for the components they want.
 */
class EntityManager {
	public:
		EntityManager();
		~EntityManager();
		void addEntity(Entity &e);	
		std::vector<Entity>& getEntities();
	private:
		std::vector<Entity> entities;	
};

#endif
