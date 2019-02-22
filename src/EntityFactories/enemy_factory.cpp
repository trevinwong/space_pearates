#include "enemy_factory.hpp"

EnemyFactory::EnemyFactory()
{
}

EnemyFactory::~EnemyFactory()
{
}

Entity EnemyFactory::build(vec2 position, vec2 scale, vec2 velocity)
{
  Program *program = new Program(shader_path("sprite.vert"), shader_path("sprite.frag"));
  Texture *texture = new Texture(texture_path("enemy0.png"), true);
  SpriteComponent *sprite = new SpriteComponent(program, texture);
  TransformComponent *transform = new TransformComponent(position, scale, 0.0f);
  MovementComponent *move = new MovementComponent(velocity, vec2(0.0, 0.0), vec2(40.0f, 40.0f), vec2(0.f, 0.f));
  ColorComponent *colour = new ColorComponent(glm::vec4(0.0f, 1.0f, 0.6f, 1.0f));
  Program *billboardProgram = new Program(shader_path("billboard.vert"), shader_path("billboard.frag"));
  HealthComponent *health = new HealthComponent(billboardProgram);
  EnemyComponent *enemy = new EnemyComponent();

  Entity e;
  e.setComponent<SpriteComponent>(sprite);
  e.setComponent<TransformComponent>(transform);
  e.setComponent<ColorComponent>(colour);
  e.setComponent<MovementComponent>(move);
  e.setComponent<HealthComponent>(health);
  e.setComponent<EnemyComponent>(enemy);
  return e;
}
