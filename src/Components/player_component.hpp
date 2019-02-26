#ifndef PLAYER_COMPONENT_H
#define PLAYER_COMPONENT_H

#include "utility.hpp"
#include "base_component.hpp"

class PlayerComponent : public BaseComponent
{
public:
  PlayerComponent();
  int jumps;
  int maxJumps;
  float jumpVelocity;
  static const int typeID = ComponentType::player;
  inline virtual int getTypeID() const { return typeID; };
  
  Texture * texture_left;	
  Texture * texture_right;
  Texture * texture_idle;

private:
  int INIT_MAX_JUMPS = 2;
  float INIT_JUMP_VELOCITY = -600.0f;
};

#endif
