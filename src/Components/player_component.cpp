#include "player_component.hpp"

PlayerComponent::PlayerComponent() 
{	
	jumps = INIT_MAX_JUMPS;
	maxJumps = INIT_MAX_JUMPS;
	jumpVelocity = INIT_JUMP_VELOCITY;
}
