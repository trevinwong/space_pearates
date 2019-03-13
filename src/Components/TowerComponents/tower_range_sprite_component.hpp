#ifndef FIRE_TOWER_RANGE_SPRITE_H
#define FIRE_TOWER_RANGE_SPRITE_H

#include "../sprite_component.hpp"

/*
Because an entity can only contain maximum one of each Compnent,
FireTowerRangeSpriteComponent inhert SpriteComponent in order to render an extra texture on a tower
*/
class TowerRangeSpriteComponent : public SpriteComponent {
public:
  TowerRangeSpriteComponent(shared_ptr<Program> _program, shared_ptr<Texture> _texture) : SpriteComponent(_program, _texture) {};
  static const int typeID = ComponentType::tower_range_sprite;
  inline virtual int getTypeID() const { return typeID; };
};
#endif