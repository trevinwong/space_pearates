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
    max_count 
  };
}

class BaseComponent 
{
public:
	virtual int getTypeID() const = 0;
};

#endif
