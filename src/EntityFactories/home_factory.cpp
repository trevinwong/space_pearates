#include "home_factory.hpp"

const vec2 BASE_SIZE = glm::vec2(70.f, 125.f);
const glm::vec4 BASE_COLOUR = glm::vec4(0.75f, 0.75f, 0.75f, 1.0f);

Entity HomeFactory::createBase(vec2 position)
{
  Entity homeEntity;
  shared_ptr<Program> program = make_shared<Program>(shader_path("sprite.vert"), shader_path("sprite.frag"));
  shared_ptr<Texture> texture = make_shared<Texture>(texture_path("teleporter.png"), true);
  shared_ptr<SpriteComponent> sprite = make_shared<SpriteComponent>(program, texture);
  shared_ptr<TransformComponent> transform = make_shared<TransformComponent>(position, BASE_SIZE, 0.0f);
  shared_ptr<ColorComponent> color = make_shared<ColorComponent>(BASE_COLOUR);
  shared_ptr<HomeComponent> home = make_shared<HomeComponent>();
  shared_ptr<Program> billboardProgram = make_shared<Program>(shader_path("billboard.vert"), shader_path("billboard.frag"));
  shared_ptr<HealthComponent> health = make_shared<HealthComponent>(billboardProgram, 100);

  homeEntity.setComponent<HomeComponent>(home);
  homeEntity.setComponent<SpriteComponent>(sprite);
  homeEntity.setComponent<TransformComponent>(transform);
  homeEntity.setComponent<ColorComponent>(color);
  homeEntity.setComponent<HealthComponent>(health);
  return homeEntity;
}