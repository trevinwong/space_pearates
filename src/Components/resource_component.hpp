#ifndef RESOURCE_COMPONENT_H
#define RESOURCE_COMPONENT_H

#include "utility.hpp"
#include "base_component.hpp"


class ResourceComponent : public BaseComponent
{
public:
	ResourceComponent(float _maxTime);
	~ResourceComponent();
	static const int typeID = ComponentType::resource;
	inline virtual int getTypeID() const { return typeID; };
    void updateTimer(float dt);
    float checkTimer(); // returns time left for resource before it is removed 

private:
    float elapsedTime; // resource is removed when elapsedTime = maxTime
    float maxTime; // total time that resource will remain on the screen 
};

#endif
