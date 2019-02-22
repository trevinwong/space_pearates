#ifndef TILE_COMPONENT_H
#define TILE_COMPONENT_H

#include "utility.hpp"
#include "base_component.hpp"

class TileComponent : public BaseComponent
{
public:
	static const int typeID = ComponentType::tile;
	inline virtual int getTypeID() const { return typeID; };
};

#endif
