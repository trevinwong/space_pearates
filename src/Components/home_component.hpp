#ifndef HOME_COMPONENT_H
#define HOME_COMPONENT_H

#include "base_component.hpp"

class HomeComponent : public BaseComponent
{
public:
  static const int typeID = ComponentType::home;
  inline virtual int getTypeID() const { return typeID; };
};

#endif