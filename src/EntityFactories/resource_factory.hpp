#ifndef RESOURCE_FACTORY_H
#define RESOURCE_FACTORY_H

#include "entity.hpp"
#include "program.hpp"
#include "Components/sprite_component.hpp"
#include "Components/transform_component.hpp"
#include "Components/color_component.hpp"
#include "Components/resource_component.hpp"
#include "Components/movement_component.hpp"
#include "Components/collision_component.hpp"

class ResourceFactory
{
    public:
    ResourceFactory();
    ~ResourceFactory();
    Entity build(glm::vec2 position, glm::vec2 scale);
};

#endif
