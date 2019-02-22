#include "base_factory.hpp"

const glm::vec2 BASE_SIZE = glm::vec2(80.f,80.f);
const glm::vec4 BASE_COLOUR = glm::vec4(0.75f,0.75f,0.75f,1.0f);

Entity BaseFactory::createBase(glm::vec2 position)
{
  Entity baseEntity;
  Program *program = new Program(shader_path("sprite.vert"), shader_path("sprite.frag"));
  Texture *texture = new Texture(texture_path("ship.png"), true);
  SpriteComponent *spriteComponent = new SpriteComponent(program, texture);
  TransformComponent *transformComponent = new TransformComponent(position, BASE_SIZE, 0.0f);
  ColorComponent *colorComponent = new ColorComponent(BASE_COLOUR);

  Program *billboardProgram = new Program(shader_path("billboard.vert"), shader_path("billboard.frag"));
  HealthComponent *health = new HealthComponent(billboardProgram);

  baseEntity.setComponent<SpriteComponent>(spriteComponent);
  baseEntity.setComponent<TransformComponent>(transformComponent);
  baseEntity.setComponent<ColorComponent>(colorComponent);
  baseEntity.setComponent<HealthComponent>(health);
  return baseEntity;
}