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
#include "../Components/collision_component.hpp"
#include "../texture.hpp"
#include "../program.hpp"

class ProjectileEntityFactory {
public:
  static Entity createAimProjectile(
    glm::vec2 size,
    glm::vec4 filterColor,
    glm::vec2 startPostion,
    float speed,
    glm::vec2 velocityDirection,
    int attackPower
  );

  /*
    e.g. if projectileNumberPerShoot = 4, then create 4 projects which spread to four directions
  */
  static vector<Entity> createSpreadProjectiles(
    int projectileNumberPerShoot,
    glm::vec2 size,
    glm::vec4 filterColor,
    glm::vec2 startPostion,
    float speed,
    int attackPower
  );

  static Entity createStarProjectiles(
    glm::vec2 size,
    glm::vec4 filterColor,
    glm::vec2 startPostion,
    glm::vec2 Velocity,
    glm::vec2 Accel,
    glm::vec2 MaxVelocity,
    glm::vec2 MaxAccel,
    int attackPower
  );
private:
  ProjectileEntityFactory();
};

#endif // !PROJECTILE_ENTITY_FACTORY_H+
