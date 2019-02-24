#ifndef HEALTH_COMPONENT_H
#define HEALTH_COMPONENT_H

#include "utility.hpp"
#include "base_component.hpp"
#include "program.hpp"

class HealthComponent : public BaseComponent
{
public:
  HealthComponent(Program *_program, float maxHP);
  ~HealthComponent();
	float health = 100.0f;
  static const int typeID = ComponentType::health;
  inline virtual int getTypeID() const { return typeID; };
  Program *program;
  float maxHP;
  float curHP;
  GLuint  quadVAO; // we only need VAO as a member as it remembers any VBOs it's associated with
};

#endif
