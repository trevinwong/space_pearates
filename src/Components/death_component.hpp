#ifndef DEATH_COMPONENT_H
#define DEATH_COMPONENT_H

#include "base_component.hpp"

class DeathComponent : public BaseComponent
{
public:
	static const int typeID = ComponentType::death;
	inline virtual int getTypeID() const { return typeID; };
};

#endif
