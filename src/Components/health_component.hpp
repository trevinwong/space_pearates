#ifndef HEALTH_COMPONENT_H
#define HEALTH_COMPONENT_H

#include "utility.hpp"
#include "base_component.hpp"
#include "program.hpp"

class HealthComponent : public BaseComponent
{
public:
  HealthComponent(shared_ptr<Program> _program, float maxHP);
  ~HealthComponent();
  void reset();

  static const int typeID = ComponentType::health;
  inline virtual int getTypeID() const { return typeID; };

  float maxHP;
  float curHP;
  shared_ptr<Program> program;
  GLuint  quadVAO; // we only need VAO as a member as it remembers any VBOs it's associated with
  GLuint VBO; // We want to create a square in which we can overlay our texture on.
};

#endif
