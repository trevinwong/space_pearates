#ifndef PLAYER_COMPONENT_H
#define PLAYER_COMPONENT_H

#include "utility.hpp"
#include "base_component.hpp"
#include "texture.hpp"

class PlayerComponent : public BaseComponent
{
public:
  PlayerComponent();
  int jumps;
  int maxJumps;
  float jumpVelocity;
  static const int typeID = ComponentType::player;
  inline virtual int getTypeID() const { return typeID; };

  shared_ptr<Texture> texture_left;
  shared_ptr<Texture> texture_right;
  shared_ptr<Texture> texture_idle;
  shared_ptr<Texture> texture_jump;

private:
  int INIT_MAX_JUMPS = 2;
  float INIT_JUMP_VELOCITY = -600.0f;
};

#endif
