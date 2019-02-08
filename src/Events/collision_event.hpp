#ifndef COLLISION_EVENT_H
#define COLLISION_EVENT_H

#include "utility.hpp"
#include "event.hpp"
#include "entity.hpp"

class CollisionEvent : public Event
{
public:
  CollisionEvent(shared_ptr<Entity> e1, shared_ptr<Entity> e2);
  ~CollisionEvent();
  static const int typeId = EventType::collision;
  inline virtual int getTypeId() const { return typeId; };
};

#endif
