#ifndef INTERPOLATION_SYSTEM_H
#define INTERPOLATION_SYSTEM_H

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/spline.hpp"

#include "utility.hpp"
#include "entity_manager.hpp"
#include "Components/spline_component.hpp"
#include "Components/transform_component.hpp"
#include "Components/collision_component.hpp"

class InterpolationSystem
{
public:
  void update(EntityManager & entityManager, float dt);

private:
  vec2 catmull_rom_spline(const vector<vec2>& cp, float t);
};

#endif
