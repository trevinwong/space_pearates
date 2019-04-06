#ifndef PLAYER_COMPONENT_H
#define PLAYER_COMPONENT_H

#include "base_component.hpp"
#include "Utility/utility.hpp"
#include "Utility/texture.hpp"
#include "Utility/timer.hpp"

enum class PlayerHealthState{
  VULNERABLE,
  INVINCIBLE
};

enum class PlayerMovementState {
  NEUTRAL,
  HITSTUN
};

class PlayerComponent : public BaseComponent
{
public:
  PlayerComponent(int _maxJumps, float _jumpVelocity);
  int jumps;
  int maxJumps;
  float jumpVelocity;
  PlayerMovementState movementState;
  Timer movementStateDuration; 

  PlayerHealthState healthState;
  Timer healthStateDuration; 

  static const int typeID = ComponentType::player;
  inline virtual int getTypeID() const { return typeID; };

  shared_ptr<Texture> texture_left;
  shared_ptr<Texture> texture_right;
  shared_ptr<Texture> texture_idle;
  shared_ptr<Texture> texture_jump;
};

#endif
