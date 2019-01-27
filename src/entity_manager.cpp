#include "entity_manager.hpp"

EntityManager::EntityManager()
{

}

EntityManager::~EntityManager()
{
}

void EntityManager::addEntity(Entity &e)
{
	entities.push_back(e);
}

std::vector<Entity>& EntityManager::getEntities()
{
	return entities;
}
