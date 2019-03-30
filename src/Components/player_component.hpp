#ifndef PLAYER_COMPONENT_H
#define PLAYER_COMPONENT_H

#include "Utility/utility.hpp"
#include "base_component.hpp"
#include "Utility/texture.hpp"

class PlayerComponent : public BaseComponent
{
public:
  PlayerComponent(int _maxJumps, float _jumpVelocity);
  int jumps;
  int maxJumps;
  float jumpVelocity;
  static const int typeID = ComponentType::player;
  inline virtual int getTypeID() const { return typeID; };

  shared_ptr<Texture> texture_left;
  shared_ptr<Texture> texture_right;
  shared_ptr<Texture> texture_idle;
  shared_ptr<Texture> texture_jump;
};

#endif
