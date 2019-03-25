#include "enemy_factory.hpp"

Entity EnemyFactory::build(vec2 position, vec2 velocity, vec2 scale, int type)
{
  Program *program = new Program(shader_path("sprite.vert"), shader_path("sprite.frag"));
  Texture *texture = new Texture(texture_path("enemy0.png"), true);
  SpriteComponent *sprite = new SpriteComponent(program, texture);
  EnemyPathComponent *pathfind = new EnemyPathComponent(type);
  TransformComponent *transform = new TransformComponent(position, scale, 0.0f);
	CollisionComponent *collision = new CollisionComponent(position, scale, 0.0f);
  MovementComponent *move = new MovementComponent(velocity, vec2(0.0, 0.0), vec2(40.0f, 40.0f), vec2(0.f, 0.f));
  ColorComponent *colour = new ColorComponent(glm::vec4(0.0f, 1.0f, 0.6f, 1.0f));
  Program *billboardProgram = new Program(shader_path("billboard.vert"), shader_path("billboard.frag"));
  HealthComponent *health = new HealthComponent(billboardProgram, 30);
  EnemyComponent *enemy = new EnemyComponent(2);
  WaterTowerFactorComponent *waterTowerFactor = new WaterTowerFactorComponent();

  Entity e;
  e.setComponent<SpriteComponent>(sprite);
  e.setComponent<TransformComponent>(transform);
	e.setComponent<CollisionComponent>(collision);
  e.setComponent<ColorComponent>(colour);
  e.setComponent<MovementComponent>(move);
  e.setComponent<WaterTowerFactorComponent>(waterTowerFactor);
  e.setComponent<HealthComponent>(health);
  e.setComponent<EnemyComponent>(enemy);
  e.setComponent<EnemyPathComponent>(pathfind);

  return e;
}
