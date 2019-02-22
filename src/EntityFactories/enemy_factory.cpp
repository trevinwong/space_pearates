#include "enemy_factory.hpp"

EnemyFactory::EnemyFactory()
{
}

EnemyFactory::~EnemyFactory()
{
}

Entity EnemyFactory::build(glm::vec2 position, glm::vec2 scale)
{
  Program *program = new Program(shader_path("sprite.vert"), shader_path("sprite.frag"));
  Texture *texture = new Texture(texture_path("enemy0.png"), true);
  SpriteComponent *sprite = new SpriteComponent(program, texture);
  TransformComponent *transform = new TransformComponent(position, scale, 0.0f);
  MovementComponent *move = new MovementComponent(glm::vec2(0.0, 1.0), glm::vec2(0.0, 0.0), vec2(100.0f, 100.0f), vec2(50.0f, 50.0f));
  ColorComponent *colour = new ColorComponent(glm::vec4(0.0f, 1.0f, 0.6f, 1.0f));
  Program *billboardProgram = new Program(shader_path("billboard.vert"), shader_path("billboard.frag"));
  HealthComponent *health = new HealthComponent(billboardProgram);

  Entity e;
  e.setComponent<SpriteComponent>(sprite);
  e.setComponent<TransformComponent>(transform);
  e.setComponent<ColorComponent>(colour);
  e.setComponent<MovementComponent>(move);
  e.setComponent<HealthComponent>(health);
  return e;
}
