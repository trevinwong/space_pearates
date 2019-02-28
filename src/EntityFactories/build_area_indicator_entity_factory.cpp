#include "build_area_indicator_entity_factory.hpp"

Entity BuildAreaIndicatorFactory::build(vec2 position, vec2 scale)
{
  Program *program = new Program(shader_path("sprite.vert"), shader_path("sprite.frag"));
  SpriteComponent *sprite = new SpriteComponent(program, new Texture(texture_path("tower_build_area.png"), true));
  TransformComponent *transform = new TransformComponent(position, scale, 0.0f);
  ColorComponent *colour = new ColorComponent(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

  Entity e;
  e.setComponent<SpriteComponent>(sprite);
  e.setComponent<TransformComponent>(transform);
  e.setComponent<ColorComponent>(colour);
  return e;
}
