#ifndef COMPONENT_H
#define COMPONENT_H

// Please increment this every time you create a new component, otherwise you will receive a segmentation fault.
int const MAX_COMPONENTS = 6;

// Organize all the static typeID's here.
int const TRANSFORM_COMPONENT_TYPEID = 0;
int const SPRITE_COMPONENT_TYPEID = 1;
int const COLOR_COMPONENT_TYPEID = 2;
int const COLLISION_COMPONENT_TYPEID = 3;
int const MAP_COMPONENT_TYPEID = 4;  // map_component.cpp/hpp
int const MOVEMENT_COMPONENT_TYPEID = 5;

class BaseComponent {
public:
	// Adding const means the function should not modify any data in the class, adding = 0 means it is a pure virtual function.
	virtual int getTypeID() const = 0;
};

#endif
