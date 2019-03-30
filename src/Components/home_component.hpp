#ifndef HOME_COMPONENT_H
#define HOME_COMPONENT_H

#include "Utility/utility.hpp"
#include "base_component.hpp"
#include "Utility/texture.hpp"

class HomeComponent : public BaseComponent
{
public:
  HomeComponent();
  static const int typeID = ComponentType::home;
  inline virtual int getTypeID() const { return typeID; };

  shared_ptr<Texture> default_texture;
  shared_ptr<Texture> alt_texture;
};

#endif