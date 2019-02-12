#ifndef COMPONENT_H
#define COMPONENT_H

namespace ComponentType {
  enum ComponentType {
    transform,
    sprite,
    color,
    collision,
    map,
    movement,
    player,
    health,
    tower_meta,
    fire_tower,               // Fire tower
    fire_tower_range_sprite,  // Fire tower
    projectile,
    max_count
  };
}

class BaseComponent 
{
public:
	virtual int getTypeID() const = 0;
};

#endif
