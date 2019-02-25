#include "background_entity_factory.hpp"

Entity BackgroundEntityFactory::createBackgroundEntity()
{
  vec2 positionOffset(-200, -200); // another weird initialization?!?! cpp...
  Program *program = new Program(shader_path("sprite.vert"), shader_path("sprite.frag"));
  Texture *texture = new Texture(texture_path("map0_bg_image.jpg"), false);
  BackgroundSpriteComponent *backgroundSpriteComponent = new BackgroundSpriteComponent(positionOffset, program, texture);

  vec2 position = vec2(0, 0);
  vec2 size = vec2(2304, 1620);   // image size
  TransformComponent *transformComponent = new TransformComponent(position, size, 0.0f);

  glm::vec4 color = glm::vec4(1, 1, 1, 1);
  ColorComponent *colorComponent = new ColorComponent(color);

  Entity backgroundEntity;
  backgroundEntity.setComponent<BackgroundSpriteComponent>(backgroundSpriteComponent);
  backgroundEntity.setComponent<TransformComponent>(transformComponent);
  backgroundEntity.setComponent<ColorComponent>(colorComponent);
  return backgroundEntity;
}
