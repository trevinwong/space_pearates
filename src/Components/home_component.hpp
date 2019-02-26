#ifndef HOME_COMPONENT_H
#define HOME_COMPONENT_H

#include "utility.hpp"
#include "base_component.hpp"
#include "program.hpp"

class HomeComponent : public BaseComponent
{
public:
  HomeComponent();
  ~HomeComponent();
  static const int typeID = ComponentType::home;
  inline virtual int getTypeID() const { return typeID; };
};

#endif