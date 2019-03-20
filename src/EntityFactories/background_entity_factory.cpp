#include "background_entity_factory.hpp"

Entity BackgroundEntityFactory::createBackgroundEntity()
{
  vec2 positionOffset(-200, -200); // another weird initialization?!?! cpp...
  shared_ptr<Program> program = make_shared<Program>(shader_path("sprite.vert"), shader_path("sprite.frag"));
  shared_ptr<Texture> texture = make_shared<Texture>(texture_path("earth_bg.png"), false);
  shared_ptr<BackgroundSpriteComponent> backgroundSpriteComponent = make_shared<BackgroundSpriteComponent>(positionOffset, program, texture);

  vec2 position = vec2(0, 0);
  vec2 size = vec2(2304, 1620);   // image size
  shared_ptr<TransformComponent> transformComponent = make_shared<TransformComponent>(position, size, 0.0f);

  glm::vec4 color = glm::vec4(1, 1, 1, 1);
  shared_ptr<ColorComponent> colorComponent = make_shared<ColorComponent>(color);

  Entity backgroundEntity;
  backgroundEntity.setComponent<BackgroundSpriteComponent>(backgroundSpriteComponent);
  backgroundEntity.setComponent<TransformComponent>(transformComponent);
  backgroundEntity.setComponent<ColorComponent>(colorComponent);
  return backgroundEntity;
}
