#ifndef RESOURCE_COMPONENT_H
#define RESOURCE_COMPONENT_H

#include "utility.hpp"
#include "base_component.hpp"
#include "Utility/timer.hpp"

class ResourceComponent : public BaseComponent
{
public:
	Timer timer;
	ResourceComponent(float _maxTime);
	static const int typeID = ComponentType::resource;
	inline virtual int getTypeID() const { return typeID; };
};

#endif
