#ifndef DEATH_COMPONENT_H
#define DEATH_COMPONENT_H

#include "utility.hpp"
#include "base_component.hpp"

class DeathComponent : public DeathComponent
{
public:
	static const int typeID = ComponentType::death;
	inline virtual int getTypeID() const { return typeID; };
};

#endif
