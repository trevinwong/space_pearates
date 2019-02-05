#ifndef PLAYER_COMPONENT_H
#define PLAYER_COMPONENT_H

#include "utility.hpp"
#include "base_component.hpp"

// For entities intended to be controled by the player.
// ATM, there should only ever be one entity with this component.
class PlayerComponent : public BaseComponent
{
public:
	PlayerComponent();
	~PlayerComponent();
	static const int typeID = PLAYER_COMPONENT_TYPEID;
	inline virtual int getTypeID() const { return typeID; };
};

#endif
