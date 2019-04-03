#include "simple_sprite_factory.hpp"

Entity SimpleSpriteFactory::create(string imageFile, GLboolean alpha, vec2 position, vec2 size, vec4 color)
{
  shared_ptr<Program> program = make_shared<Program>(shader_path("sprite.vert"), shader_path("sprite.frag"));

  std::string imagePath = string(texture_path("")) + imageFile;
  shared_ptr<Texture> texture = make_shared<Texture>(imagePath.c_str(), alpha);
  shared_ptr<SpriteComponent> spriteComponent = make_shared<SpriteComponent>(program, texture);

  shared_ptr<TransformComponent> transformComponent = make_shared<TransformComponent>(position, size, 0.0f);

  shared_ptr<ColorComponent> colorComponent = make_shared<ColorComponent>(color);

  Entity spriteEntity;
  spriteEntity.setComponent<SpriteComponent>(spriteComponent);
  spriteEntity.setComponent<TransformComponent>(transformComponent);
  spriteEntity.setComponent<ColorComponent>(colorComponent);
  return spriteEntity;
}

Entity SimpleSpriteFactory::create()
{
  Entity e = create("blank.png", true, vec2(0.f, 0.f), vec2(10.0f, 10.0f), vec4(1, 1, 1, 1));
  return e;
}
