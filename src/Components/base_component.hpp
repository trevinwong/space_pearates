#ifndef COMPONENT_H
#define COMPONENT_H

namespace ComponentType {
  enum ComponentType {
    transform,
    sprite,
    color, // what are we, Amurican?
    collision,
    map,
    movement,
    player,
    max_count // not sure if there's a better way to get enum count
  };
}

class BaseComponent 
{
public:
	virtual int getTypeID() const = 0;
};

#endif
