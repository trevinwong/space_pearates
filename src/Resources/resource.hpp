#ifndef RESOURCE_H
#define RESOURCE_H

#include "entity_manager.hpp"
#include "EntityFactories/resource_factory.hpp"
#include "../Systems/tile_map_system.hpp"

class Resource
{
public:
  Resource();
  ~Resource();
  void loadResource(glm::vec2 screen, EntityManager& entities);
private:
  ResourceFactory factory;
};

#endif
