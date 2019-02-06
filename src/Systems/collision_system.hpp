#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include "utility.hpp"
#include "entity.hpp"
#include "subscriber.hpp"
#include "Components/movement_component.hpp"
#include "Components/collision_component.hpp"
#include "Components/transform_component.hpp"
#include "Systems/event_system.hpp"
#include "Events/collision_event.hpp"

class CollisionSystem : public Subscriber
{
public:
  void checkCollisions(EventSystem &eventSystem, vector<Entity> &entities);
  void processEvent(Event *event);
private:
  bool isCollision(Entity &one, Entity &two);
};

#endif


