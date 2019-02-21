#include "projectile_entity_factory.hpp"

Entity ProjectileEntityFactory::createAimProjectile(glm::vec2 size, glm::vec4 filterColor, glm::vec2 startPostion, float speed, glm::vec2 velocityDirection, int attackPower)
{
  Entity projectileEntity;

  TransformComponent *transformComponent = new TransformComponent(startPostion, size, 0.0f);  // TODO: calculate rotation by velocityDirection
  ColorComponent *colorComponent = new ColorComponent(filterColor);

  glm::vec2 acc(0.0f, 0.0f);
  glm::vec2 velocity = glm::normalize(velocityDirection) * speed;

  MovementComponent *movementComponent = new MovementComponent(velocity, acc, vec2(100.0f, 100.0f), vec2(0.0f, 0.0f));
  movementComponent->offScreenOK = true;  // a projectile can be off screen and then be destroyed by projectile_destroy_system

  ProjectileComponent *projectileComponent = new ProjectileComponent(attackPower);

  // SpriteComponent
  Program *towerProgram = new Program(shader_path("sprite.vert"), shader_path("sprite.frag"));
  Texture *towerTexture = new Texture(texture_path("fire_projectile.png"), true);
  SpriteComponent *spriteComponent = new SpriteComponent(towerProgram, towerTexture);

  projectileEntity.setComponent<SpriteComponent>(spriteComponent);
  projectileEntity.setComponent<TransformComponent>(transformComponent);
  projectileEntity.setComponent<ColorComponent>(colorComponent);
  projectileEntity.setComponent<MovementComponent>(movementComponent);
  projectileEntity.setComponent<ProjectileComponent>(projectileComponent);

  return projectileEntity;
}

