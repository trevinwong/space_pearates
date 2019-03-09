#include "home_factory.hpp"

const vec2 BASE_SIZE = glm::vec2(70.f, 125.f);
const glm::vec4 BASE_COLOUR = glm::vec4(0.75f, 0.75f, 0.75f, 1.0f);

Entity HomeFactory::createBase(vec2 position)
{
  Entity homeEntity;
  Program *program = new Program(shader_path("sprite.vert"), shader_path("sprite.frag"));
  Texture *texture = new Texture(texture_path("teleporter.png"), true);
  SpriteComponent *sprite = new SpriteComponent(program, texture);
  TransformComponent *transform = new TransformComponent(position, BASE_SIZE, 0.0f);
  ColorComponent *color = new ColorComponent(BASE_COLOUR);
  HomeComponent *home = new HomeComponent();
  Program *billboardProgram = new Program(shader_path("billboard.vert"), shader_path("billboard.frag"));
  HealthComponent *health = new HealthComponent(billboardProgram, 100);

  homeEntity.setComponent<HomeComponent>(home);
  homeEntity.setComponent<SpriteComponent>(sprite);
  homeEntity.setComponent<TransformComponent>(transform);
  homeEntity.setComponent<ColorComponent>(color);
  homeEntity.setComponent<HealthComponent>(health);
  return homeEntity;
}