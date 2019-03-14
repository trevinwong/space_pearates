#ifndef DAMAGE_COMPONENT_H
#define DAMAGE_COMPONENT_H

#include "Utility/utility.hpp"
#include "base_component.hpp"

class DamageComponent : public BaseComponent
{
public:
	float power;
	DamageComponent(float _power);

	static const int typeID = ComponentType::damage;
	inline virtual int getTypeID() const { return typeID; };
};

#endif