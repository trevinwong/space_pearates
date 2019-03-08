#ifndef OFFSCREEN_GARBAGE_SYSTEM_H
#define OFFSCREEN_GARBAGE_SYSTEM_H

#include <vector>
#include "utility.hpp"
#include "entity.hpp"
#include "entity_manager.hpp"
#include "../Components/transform_component.hpp"

/*
  Destory offscreen entities

  e.g.
  if component_types = { ComponentType::A, ComponentType::E, ComponentType::F }
  then all entities which contain A OR E OR F will be checked
*/
class OffscreenGarbageSystem {
public:
  void destroyEntitiesContaining(EntityManager & entityManager, ComponentType::ComponentType type);
  void destroyEntitiesContaining(EntityManager & entityManager, vector<int> component_types);
  void destroyEntitiesContainingAll(EntityManager & entityManager, vector<int> component_types);
private:
  void destroyOffscreen(EntityManager & entityManager, vector<shared_ptr<Entity>> entities);
};

#endif // !OFFSCREEN_GARBAGE_SYSTEM_H
