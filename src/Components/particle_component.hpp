#ifndef PARTICLE_COMPONENT_H
#define PARTICLE_COMPONENT_H

#include "utility.hpp"
#include "base_component.hpp"
#include "../Utility/timer.hpp" 
#include "entity.hpp"

class ParticleComponent : public BaseComponent
{
public:
    ParticleComponent(float _lifetime) : lifetime(_lifetime), timer(_lifetime) {}
    static const int typeID = ComponentType::particle;
    inline virtual int getTypeID() const { return typeID; };

    Timer timer;
    float lifetime;
    float angle;
    float speed; 
    glm::vec2 particleScale;
    bool active;
};

#endif