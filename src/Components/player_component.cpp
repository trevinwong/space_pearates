#include "player_component.hpp"

PlayerComponent::PlayerComponent() 
{	
	jumps = INIT_MAX_JUMPS;
	maxJumps = INIT_MAX_JUMPS;
	jumpVelocity = INIT_JUMP_VELOCITY;

	texture_left = new Texture(texture_path("player-left0.png"), true);
	texture_right = new Texture(texture_path("player-right0.png"), true);
	texture_idle = new Texture(texture_path("player-idle0.png"), true);
	texture_jump = new Texture(texture_path("jump.png"), true);
}
