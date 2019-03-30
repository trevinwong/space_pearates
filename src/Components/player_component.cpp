#include "player_component.hpp"

PlayerComponent::PlayerComponent(int _maxJumps, float _jumpVelocity) :
  maxJumps(_maxJumps),
  jumpVelocity(_jumpVelocity)
{	
  jumps = 0;
	texture_left = make_shared<Texture>(texture_path("player-left0.png"), true);
	texture_right = make_shared<Texture>(texture_path("player-right0.png"), true);
	texture_idle = make_shared<Texture>(texture_path("player-idle0.png"), true);
	texture_jump = make_shared<Texture>(texture_path("jump.png"), true);
}
