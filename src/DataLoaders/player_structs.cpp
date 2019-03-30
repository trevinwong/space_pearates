#include "player_structs.hpp"

PlayerData::PlayerData()
{
}

PlayerData::PlayerData(vec2 _size, vec2 _maxVelocity, vec2 _maxAccel, float _health, int _maxJumps, float _jumpVelocity) :
  size(_size),
  maxVelocity(_maxVelocity),
  maxAccel(_maxAccel),
  health(_health),
  maxJumps(_maxJumps),
  jumpVelocity(_jumpVelocity)
{
}
