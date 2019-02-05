#ifndef COLLISION_EVENT_H
#define COLLISION_EVENT_H

#include "utility.hpp"

class CollisionEvent : public Event
{
public:
	static const string typeName = "CollisionEvent";	
	inline virtual string getTypeName() const { return typeName; };
};

#endif
