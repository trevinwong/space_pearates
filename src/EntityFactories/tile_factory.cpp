#include "tile_factory.hpp"

Entity TileFactory::build(int type, vec2 position, vec2 scale)
{
  Program *program = new Program(shader_path("sprite.vert"), shader_path("sprite.frag"));
  SpriteComponent *sprite = new SpriteComponent(program, new Texture(texture_path("tile_block.png"), true));
  TransformComponent *transform = new TransformComponent(position, scale, 0.0f);
  CollisionComponent *collision = new CollisionComponent(position, scale, 0.0f);
  ColorComponent *colour = new ColorComponent(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
  TileComponent *tile = new TileComponent();

  Entity e;
  e.setComponent<SpriteComponent>(sprite);
  e.setComponent<TransformComponent>(transform);
  e.setComponent<CollisionComponent>(collision);
  e.setComponent<ColorComponent>(colour);
  e.setComponent<TileComponent>(tile);
  return e;
}
