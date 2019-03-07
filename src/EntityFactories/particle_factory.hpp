#ifndef PARTICLE_FACTORY_H
#define PARTICLE_FACTORY_H

#include "entity.hpp"
#include "program.hpp"
#include "Components/sprite_component.hpp"
#include "Components/transform_component.hpp"
#include "Components/color_component.hpp"
#include "Components/movement_component.hpp"
#include "Components/particle_component.hpp"

class ParticleFactory 
{
    public:
        static Entity build(glm::vec2 position);
        static float randomAngle();
};

#endif
