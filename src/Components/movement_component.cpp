#include "movement_component.hpp"

MovementComponent::MovementComponent(vec2 Accel, vec2 Velocity, vec2 MaxVelocity, vec2 MaxAccel) :
	accel(Accel), velocity(Velocity), maxVelocity(MaxVelocity), maxAccel(MaxAccel)
{
}
