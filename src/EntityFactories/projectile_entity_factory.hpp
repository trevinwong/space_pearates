#ifndef PROJECTILE_ENTITY_FACTORY_H
#define PROJECTILE_ENTITY_FACTORY_H

#include <vector>
#include "utility.hpp"
#include "entity.hpp"
#include "entity_manager.hpp"
#include "../Components/transform_component.hpp"
#include "../Components/movement_component.hpp"
#include "../Components/color_component.hpp"
#include "../Components/sprite_component.hpp"
#include "../Components/projectile_component.hpp"
#include "../texture.hpp"
#include "../program.hpp"

class ProjectileEntityFactory {
public:
  static Entity createAimProjectile(
    glm::vec2 size,
    glm::vec4 filterColor,
    glm::vec2 startPostion,
    float velocity,
    glm::vec2 velocityDirection,
    int attackPower
  );
  ~ProjectileEntityFactory();
private:
  ProjectileEntityFactory();
};

#endif // !PROJECTILE_ENTITY_FACTORY_H+
