#ifndef BACKGROUND_SPRITE_COMPONENT_H
#define BACKGROUND_SPRITE_COMPONENT_H

#include "sprite_component.hpp"

class BackgroundSpriteComponent : public SpriteComponent {
public:
  // initPosition indicate the position of background image when the player at (0, 0)
  BackgroundSpriteComponent(vec2 _positionOffset, Program *_program, Texture *_texture) :
    positionOffset(_positionOffset),
    SpriteComponent(_program, _texture) {};
  static const int typeID = ComponentType::background_sprite;
  inline virtual int getTypeID() const { return typeID; };

  vec2 positionOffset;
};
#endif