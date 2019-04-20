#include "projectile_entity_factory.hpp"

Entity ProjectileEntityFactory::createAimProjectile(vec2 size, glm::vec4 filterColor, vec2 startPosition, float speed, vec2 velocityDirection, int attackPower, char* texture)
{
  shared_ptr<Program> towerProgram = make_shared<Program>(shader_path("sprite.vert"), shader_path("sprite.frag"));
  shared_ptr<Texture> towerTexture = make_shared<Texture>(texture, true);
  shared_ptr<SpriteComponent> sprite = make_shared<SpriteComponent>(towerProgram, towerTexture);
  shared_ptr<ColorComponent> color = make_shared<ColorComponent>(filterColor);

  shared_ptr<TransformComponent> transform = make_shared<TransformComponent>(startPosition, size, 0.0f);  // TODO: calculate rotation by velocityDirection
  shared_ptr<CollisionComponent> collision = make_shared<CollisionComponent>(startPosition, size, 0.0f);

  vec2 velocity = velocityDirection * speed;
  shared_ptr<MovementComponent> movement = make_shared<MovementComponent>(velocity, vec2(0.0f, 0.0f), vec2(300.0f, 300.0f), vec2(0.0f, 0.0f));
  movement->offScreenOK = true; // a projectile can be off screen and then be destroyed by projectile_destroy_system

  shared_ptr<ProjectileComponent> projectile = make_shared<ProjectileComponent>(attackPower);

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

    Entity entity = createAimProjectile(size, filterColor, startPosition, speed, velocityDirection, attackPower, texture_path("light_projectile.png"));
    spreadProjectileEntities.push_back(entity);
  }

  return spreadProjectileEntities;
}

Entity ProjectileEntityFactory::createStarProjectile(vec2 size, glm::vec4 filterColor, vec2 startPosition, vec2 velocity, vec2 accel, vec2 maxVelocity, vec2 maxAccel, int attackPower)
{
  shared_ptr<Program> towerProgram = make_shared<Program>(shader_path("sprite.vert"), shader_path("sprite.frag"));
  shared_ptr<Texture> towerTexture = make_shared<Texture>(texture_path("star_projectile.png"), true);
  shared_ptr<SpriteComponent> sprite = make_shared<SpriteComponent>(towerProgram, towerTexture);
  shared_ptr<ColorComponent> color = make_shared<ColorComponent>(filterColor);

  shared_ptr<TransformComponent> transform = make_shared<TransformComponent>(startPosition, size, 0.0f);  // TODO: calculate rotation by velocityDirection
  shared_ptr<CollisionComponent> collision = make_shared<CollisionComponent>(startPosition, size, 0.0f);

  shared_ptr<MovementComponent> movement = make_shared<MovementComponent>(velocity, accel, maxVelocity, maxAccel);
  movement->offScreenOK = true;  // a projectile can be off screen and then be destroyed by projectile_destroy_system

  shared_ptr<ProjectileComponent> projectile = make_shared<ProjectileComponent>(attackPower);

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
  shared_ptr<Program> towerProgram = make_shared<Program>(shader_path("sprite.vert"), shader_path("sprite.frag"));
  shared_ptr<Texture> towerTexture = make_shared<Texture>(texture_path("boomerang.png"), true);
  shared_ptr<SpriteComponent> sprite = make_shared<SpriteComponent>(towerProgram, towerTexture);
  shared_ptr<ColorComponent> color = make_shared<ColorComponent>(filterColor);

  vec2 leftTopPosition = originPosition - size * 0.5f;
  shared_ptr<TransformComponent> transform = make_shared<TransformComponent>(leftTopPosition, size, 0.0f);
  shared_ptr<CollisionComponent> collision = make_shared<CollisionComponent>(leftTopPosition, size, 0.0f);

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
  shared_ptr<SplineComponent> spline = make_shared<SplineComponent>(controlPoints);
  shared_ptr<ProjectileComponent> projectile = make_shared<ProjectileComponent>(attackPower, true);

  Entity projectileEntity;
  projectileEntity.setComponent<SpriteComponent>(sprite);
  projectileEntity.setComponent<ColorComponent>(color);
  projectileEntity.setComponent<TransformComponent>(transform);
  projectileEntity.setComponent<CollisionComponent>(collision);
  projectileEntity.setComponent<SplineComponent>(spline);
  projectileEntity.setComponent<ProjectileComponent>(projectile);
  return projectileEntity;
}

