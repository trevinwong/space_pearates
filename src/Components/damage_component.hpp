#ifndef DAMAGE_COMPONENT_H
#define DAMAGE_COMPONENT_H

#include "Utility/utility.hpp"
#include "base_component.hpp"

class DamageComponent : public BaseComponent
{
public:
	vector<float> damage_instances;
	DamageComponent(float damage);
	void addDamageInstance(float damage);

	static const int typeID = ComponentType::damage;
	inline virtual int getTypeID() const { return typeID; };
};

#endif
