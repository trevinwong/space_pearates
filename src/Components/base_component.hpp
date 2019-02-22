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
    enemy,
    enemy_spawn,
    player,
    health,
    tower_meta,
    fire_tower,
    fire_tower_range_sprite,
    projectile,
		tile,
    max_count
  };
}

class BaseComponent
{
public:
	virtual int getTypeID() const = 0;
};

#endif
