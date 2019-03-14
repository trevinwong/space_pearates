#ifndef MOVEMENT_COMPONENT_H
#define MOVEMENT_COMPONENT_H

#include "Utility/utility.hpp"
#include "base_component.hpp"

class MovementComponent : public BaseComponent
{
public:
	MovementComponent(vec2 Velocity, vec2 Accel, vec2 MaxVelocity, vec2 MaxAccel);
	vec2 accel, velocity, maxVelocity, maxAccel;
	bool offScreenOK = true;
	static const int typeID = ComponentType::movement;
	inline virtual int getTypeID() const { return typeID; };
};

#endif
