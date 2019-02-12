#ifndef LIGHT_TOWER_RANGE_SPRITE_H
#define LIGHT_TOWER_RANGE_SPRITE_H

#include "../sprite_component.hpp"

/*
Because an entity can only contain maximum one of each Compnent,
LightTowerRangeSpriteComponent inhert SpriteComponent in order to render an extra texture on a tower
*/
class LightTowerRangeSpriteComponent : public SpriteComponent {
public:
  LightTowerRangeSpriteComponent(Program *_program, Texture *_texture) : SpriteComponent(_program, _texture) {};
  ~LightTowerRangeSpriteComponent();
  static const int typeID = ComponentType::light_tower_range_sprite;
  inline virtual int getTypeID() const { return typeID; };
};
#endif