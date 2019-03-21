#ifndef COMPONENT_H
#define COMPONENT_H

namespace ComponentType {
  enum ComponentType {
    transform,
    sprite,
    color,
    collision,
    movement,
    water_tower_factor,
    map,
    enemy,
    background_sprite,
    player,
    wallet,
    health,
    tower_meta,
    attack_tower,
    tower_range_sprite,
    tower_ui_button,
    tower_ui_button_meta,
    tower_ui_state,
    menu_ui,
    projectile,
    spline,
    tile,
    resource,
    animated,
    home,
    damage,
    death,
    waveset,
    particle,
    max_count // Add above.
  };
}

class BaseComponent
{
public:
  virtual int getTypeID() const = 0;
};

#endif
