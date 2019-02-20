#ifndef FIRE_TOWER_RANGE_SPRITE_H
#define FIRE_TOWER_RANGE_SPRITE_H

#include "../sprite_component.hpp"

/*
Because an entity can only contain maximum one of each Compnent,
FireTowerRangeSpriteComponent inhert SpriteComponent in order to render an extra texture on a tower
*/
class FireTowerRangeSpriteComponent: public SpriteComponent {
  public:
    FireTowerRangeSpriteComponent(Program *_program, Texture *_texture): SpriteComponent(_program, _texture){};
    ~FireTowerRangeSpriteComponent();
    static const int typeID = ComponentType::fire_tower_range_sprite;
    inline virtual int getTypeID() const { return typeID; };
};
#endif