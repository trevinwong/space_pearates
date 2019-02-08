#include "entity_manager.hpp"

EntityManager::EntityManager()
{

}

EntityManager::~EntityManager()
{
}

void EntityManager::addEntity(Entity e)
{
	entities.push_back(make_shared<Entity>(e));
}

std::vector<shared_ptr<Entity>> EntityManager::getEntities()
{
	return entities;
}
