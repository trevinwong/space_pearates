#include "projectile_entity_factory.hpp"

Entity ProjectileEntityFactory::createAimProjectile(vec2 size, glm::vec4 filterColor, vec2 startPosition, float speed, vec2 velocityDirection, int attackPower)
{
  Program *towerProgram = new Program(shader_path("sprite.vert"), shader_path("sprite.frag"));
  Texture *towerTexture = new Texture(texture_path("fire_projectile.png"), true);
  SpriteComponent *sprite = new SpriteComponent(towerProgram, towerTexture);
  ColorComponent *color = new ColorComponent(filterColor);

  TransformComponent *transform = new TransformComponent(startPosition, size, 0.0f);  // TODO: calculate rotation by velocityDirection
  CollisionComponent *collision = new CollisionComponent(startPosition, size, 0.0f);

  vec2 velocity = velocityDirection * speed;
  MovementComponent *movement = new MovementComponent(velocity, vec2(0.0f, 0.0f), vec2(100.0f, 100.0f), vec2(0.0f, 0.0f));
  movement->offScreenOK = true; // a projectile can be off screen and then be destroyed by projectile_destroy_system

  ProjectileComponent *projectile = new ProjectileComponent(attackPower);

  Entity projectileEntity;
  projectileEntity.setComponent<SpriteComponent>(sprite);
  projectileEntity.setComponent<ColorComponent>(color);
  projectileEntity.setComponent<TransformComponent>(transform);
  projectileEntity.setComponent<CollisionComponent>(collision);
  projectileEntity.setComponent<MovementComponent>(movement);
  projectileEntity.setComponent<ProjectileComponent>(projectile);
  return projectileEntity;
}

vector<Entity> ProjectileEntityFactory::createSpreadProjectiles(int projectileNumberPerShoot, vec2 size, glm::vec4 filterColor, vec2 startPosition, float speed, int attackPower)
{
  vector<Entity> spreadProjectileEntities;

  // e.g. if projectileNumberPerShoot = 4, then 4 projectiles will have 0, 90, 90*2, 90*3 degree direction
  float angleSize = 360.0f / (float)(projectileNumberPerShoot);

  // base on projectileNumberPerShoot compute directions
  for (int i = 0; i < projectileNumberPerShoot; i++) {
    float radians = glm::pi<float>() * angleSize * (float)i / 180.0f;
    vec2 velocityDirection = vec2(cos(radians), sin(radians));

    Entity entity = createAimProjectile(size, filterColor, startPosition, speed, velocityDirection, attackPower);
    spreadProjectileEntities.push_back(entity);
  }

  return spreadProjectileEntities;
}

Entity ProjectileEntityFactory::createStarProjectile(vec2 size, glm::vec4 filterColor, vec2 startPosition, vec2 velocity, vec2 accel, vec2 maxVelocity, vec2 maxAccel, int attackPower)
{
  Program *towerProgram = new Program(shader_path("sprite.vert"), shader_path("sprite.frag"));
  Texture *towerTexture = new Texture(texture_path("star_projectile.png"), true);
  SpriteComponent *sprite = new SpriteComponent(towerProgram, towerTexture);
  ColorComponent *color = new ColorComponent(filterColor);

  TransformComponent *transform = new TransformComponent(startPosition, size, 0.0f);  // TODO: calculate rotation by velocityDirection
  CollisionComponent *collision = new CollisionComponent(startPosition, size, 0.0f);

  MovementComponent *movement = new MovementComponent(velocity, accel, maxVelocity, maxAccel);
  movement->offScreenOK = true;  // a projectile can be off screen and then be destroyed by projectile_destroy_system

  ProjectileComponent *projectile = new ProjectileComponent(attackPower);

  Entity projectileEntity;
  projectileEntity.setComponent<SpriteComponent>(sprite);
  projectileEntity.setComponent<ColorComponent>(color);
  projectileEntity.setComponent<TransformComponent>(transform);
  projectileEntity.setComponent<CollisionComponent>(collision);
  projectileEntity.setComponent<MovementComponent>(movement);
  projectileEntity.setComponent<ProjectileComponent>(projectile);
  return projectileEntity;
}

Entity ProjectileEntityFactory::createBoomerang(vec2 originPosition, vec2 enemyPosition, int attackPower, vec2 size, glm::vec4 filterColor)
{
  Program *towerProgram = new Program(shader_path("sprite.vert"), shader_path("sprite.frag"));
  Texture *towerTexture = new Texture(texture_path("boomerang.png"), true);
  SpriteComponent *sprite = new SpriteComponent(towerProgram, towerTexture);
  ColorComponent *color = new ColorComponent(filterColor);

  vec2 leftTopPosition = originPosition - size * 0.5f;
  TransformComponent *transform = new TransformComponent(leftTopPosition, size, 0.0f);
  CollisionComponent *collision = new CollisionComponent(leftTopPosition, size, 0.0f);

  float fixedRange = 200.0f; //TODO maybe as power-up
  vec2 shootDir = glm::normalize(enemyPosition - originPosition);
  vec2 perpendicularShootDir = vec2(shootDir.y, -shootDir.x);
  vec2 targetPosition = originPosition + shootDir * fixedRange;
  vec2 rotatedRight = targetPosition + perpendicularShootDir * 150.0f;

  vector<vec2> controlPoints = {
    originPosition,
    targetPosition,
    rotatedRight,
    originPosition
  };
  SplineComponent *spline = new SplineComponent(controlPoints);
  ProjectileComponent *projectile = new ProjectileComponent(attackPower, true);

  Entity projectileEntity;
  projectileEntity.setComponent<SpriteComponent>(sprite);
  projectileEntity.setComponent<ColorComponent>(color);
  projectileEntity.setComponent<TransformComponent>(transform);
  projectileEntity.setComponent<CollisionComponent>(collision);
  projectileEntity.setComponent<SplineComponent>(spline);
  projectileEntity.setComponent<ProjectileComponent>(projectile);
  return projectileEntity;
}

