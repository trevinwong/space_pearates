#include "movement_component.hpp"

MovementComponent::MovementComponent(vec2 Velocity, vec2 Accel, vec2 MaxVelocity, vec2 MaxAccel) :
	velocity(Velocity), accel(Accel), maxVelocity(MaxVelocity), maxAccel(MaxAccel)
{
}
