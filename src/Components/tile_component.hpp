#ifndef TILE_COMPONENT_H
#define TILE_COMPONENT_H

#include "Utility/utility.hpp"
#include "base_component.hpp"

class TileComponent : public BaseComponent
{
public:
  TileComponent(bool _isPhysical=true);
  bool isPhysical;

	static const int typeID = ComponentType::tile;
	inline virtual int getTypeID() const { return typeID; };
};

#endif
