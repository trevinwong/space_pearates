#ifndef PROJECTILE_ENTITY_FACTORY_H
#define PROJECTILE_ENTITY_FACTORY_H

#include <vector>
#include "Utility/utility.hpp"
#include "entity.hpp"
#include "entity_manager.hpp"
#include "../Components/transform_component.hpp"
#include "../Components/movement_component.hpp"
#include "../Components/color_component.hpp"
#include "../Components/sprite_component.hpp"
#include "../Components/projectile_component.hpp"
#include "../Components/collision_component.hpp"
#include "../Components/spline_component.hpp"
#include "../Utility/texture.hpp"
#include "../Utility/program.hpp"
#include "../Components/mesh_component.hpp"
#include "../Components/mesh_collision_component.hpp"

class ProjectileEntityFactory {
public:
  static Entity createAimProjectile(
    vec2 size,
    glm::vec4 filterColor,
    vec2 startPosition,
    float speed,
    vec2 velocityDirection,
    int attackPower,
    char* texture
  );

  /*
    e.g. if projectileNumberPerShoot = 4, then create 4 projects which spread to four directions
  */
  static vector<Entity> createSpreadProjectiles(
    int projectileNumberPerShoot,
    vec2 size,
    glm::vec4 filterColor,
    vec2 startPosition,
    float speed,
    int attackPower
  );

  static Entity createStarProjectile(
    vec2 size,
    glm::vec4 filterColor,
    vec2 startPosition,
    vec2 Velocity,
    vec2 Accel,
    vec2 MaxVelocity,
    vec2 MaxAccel,
    int attackPower
  );

  static Entity createBoomerang(
    vec2 startPosition,
    vec2 enemyPosition,
    int attackPower,
    vec2 size = vec2(25.0, 25.0) * SCALING_FACTOR,
    glm::vec4 filterColor = glm::vec4(1, 1, 1, 1)
  );

private:
  ProjectileEntityFactory();
};

#endif // !PROJECTILE_ENTITY_FACTORY_H+
