#ifndef COLLISION_EVENT_H
#define COLLISION_EVENT_H

#include "utility.hpp"
#include "event.hpp"

class CollisionEvent : public Event
{
public:
  CollisionEvent();
  ~CollisionEvent();
  static const int typeId = EventType::collision;
  inline virtual int getTypeId() const { return typeId; };
};

#endif
