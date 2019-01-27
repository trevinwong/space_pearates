#ifndef COLOR_COMPONENT_H
#define COLOR_COMPONENT_H

#include "utility.hpp"
#include "component.hpp"

// Change to RGBA after we get everything running.
class ColorComponent : public BaseComponent
{ 
  public:
    ColorComponent(glm::vec3 _RGB);
		~ColorComponent();
		glm::vec3 RGB;
    static const int typeID = COLOR_COMPONENT_TYPEID;
    inline virtual int getTypeID() const { return typeID; };
};

#endif
