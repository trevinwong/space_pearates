#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include "utility.hpp"
#include "entity.hpp"
#include "Components/movement_component.hpp"
#include "Components/collision_component.hpp"
#include "Components/transform_component.hpp"
#include "Systems/event_system.hpp"
#include "Events/collision_event.hpp"

class CollisionSystem
{
public:
  void checkCollisions(EventSystem &eventSystem, vector<shared_ptr<Entity>> entities);
private:
  bool isCollision(shared_ptr<Entity> one, shared_ptr<Entity> two);
};

#endif


