#ifndef COMPONENT_H
#define COMPONENT_H

int const MAX_COMPONENTS = 100;

int const TRANSFORM_COMPONENT_TYPEID = 0;
int const SPRITE_COMPONENT_TYPEID = 1;
int const COLOR_COMPONENT_TYPEID = 2;
int const COLLISION_COMPONENT_TYPEID = 3;
int const MAP_COMPONENT_TYPEID = 4;  
int const MOVEMENT_COMPONENT_TYPEID = 5;
int const PLAYER_COMPONENT_TYPEID = 6;

class BaseComponent 
{
public:
	virtual int getTypeID() const = 0;
};

#endif
