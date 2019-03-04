#include "projectile_entity_factory.hpp"

Entity ProjectileEntityFactory::createAimProjectile(vec2 size, glm::vec4 filterColor, vec2 startPostion, float speed, vec2 velocityDirection, int attackPower)
{
  Entity projectileEntity;

  TransformComponent *transformComponent = new TransformComponent(startPostion, size, 0.0f);  // TODO: calculate rotation by velocityDirection
  ColorComponent *colorComponent = new ColorComponent(filterColor);

  vec2 acc(0.0f, 0.0f);
  vec2 velocity = velocityDirection * speed;
  CollisionComponent *collision = new CollisionComponent(startPostion, size, 0.0f);

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
  projectileEntity.setComponent<CollisionComponent>(collision);

  return projectileEntity;
}

vector<Entity> ProjectileEntityFactory::createSpreadProjectiles(int projectileNumberPerShoot, vec2 size, glm::vec4 filterColor, vec2 startPostion, float speed, int attackPower)
{
  std::vector<Entity> spreadProjectileEntities;

  // e.g. if projectileNumberPerShoot = 4, then 4 projectiles will have 0, 90, 90*2, 90*3 degree direction
  float angleSize = 360.0f / (float)(projectileNumberPerShoot);
  vec2 direction = vec2(0.0, 0.0);
  // base on projectileNumberPerShoot compute directions
  for (int i = 0; i < projectileNumberPerShoot; i++) {
    float radians = glm::pi<float>() * angleSize * (float)i / 180.0f;
    vec2 velocityDirection = vec2(cos(radians), sin(radians));

    Entity entity = createAimProjectile(size, filterColor, startPostion, speed, velocityDirection, attackPower);
    spreadProjectileEntities.push_back(entity);
  }

  return spreadProjectileEntities;
}

Entity ProjectileEntityFactory::createStarProjectiles(glm::vec2 size, glm::vec4 color, glm::vec2 startPostion, glm::vec2 velocity, glm::vec2 accel, glm::vec2 maxVelocity, glm::vec2 maxAccel, int attackPower)
{
  Entity projectileEntity;

  TransformComponent *transformComponent = new TransformComponent(startPostion, size, 0.0f);  // TODO: calculate rotation by velocityDirection
  ColorComponent *colorComponent = new ColorComponent(color);

  CollisionComponent *collision = new CollisionComponent(startPostion, size, 0.0f);

  MovementComponent *movementComponent = new MovementComponent(velocity, accel, maxVelocity, maxAccel);
  movementComponent->offScreenOK = true;  // a projectile can be off screen and then be destroyed by projectile_destroy_system

  ProjectileComponent *projectileComponent = new ProjectileComponent(attackPower);

  // SpriteComponent
  Program *towerProgram = new Program(shader_path("sprite.vert"), shader_path("sprite.frag"));
  Texture *towerTexture = new Texture(texture_path("star_projectile.png"), true);
  SpriteComponent *spriteComponent = new SpriteComponent(towerProgram, towerTexture);

  projectileEntity.setComponent<SpriteComponent>(spriteComponent);
  projectileEntity.setComponent<TransformComponent>(transformComponent);
  projectileEntity.setComponent<ColorComponent>(colorComponent);
  projectileEntity.setComponent<MovementComponent>(movementComponent);
  projectileEntity.setComponent<ProjectileComponent>(projectileComponent);
  projectileEntity.setComponent<CollisionComponent>(collision);

  return projectileEntity;
}

