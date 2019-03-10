#include "tile_factory.hpp"

Entity TileFactory::buildTile(vec2 position, vec2 scale)
{
  shared_ptr<Program> program = make_shared<Program>(shader_path("sprite.vert"), shader_path("sprite.frag"));
  shared_ptr<SpriteComponent> sprite = make_shared<SpriteComponent>(program, make_shared<Texture>(texture_path("tile_block.png"), true));
  shared_ptr<TransformComponent> transform = make_shared<TransformComponent>(position, scale, 0.0f);
 // CollisionComponent> collision = make_shared<CollisionComponent(position, scale, 0.0f);
  shared_ptr<ColorComponent> colour = make_shared<ColorComponent>(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
  shared_ptr<TileComponent> tile = make_shared<TileComponent>();

  Entity e;
  e.setComponent<SpriteComponent>(sprite);
  e.setComponent<TransformComponent>(transform);
//  e.setComponent<CollisionComponent>(collision);
  e.setComponent<ColorComponent>(colour);
  e.setComponent<TileComponent>(tile);
  return e;
}

Entity TileFactory::buildTowerAreaIndicator(vec2 position, vec2 scale)
{
  shared_ptr<Program> program = make_shared<Program>(shader_path("sprite.vert"), shader_path("sprite.frag"));
  shared_ptr<SpriteComponent> sprite = make_shared<SpriteComponent>(program, make_shared<Texture>(texture_path("tower_build_area.png"), true));
  shared_ptr<TransformComponent> transform = make_shared<TransformComponent>(position, scale, 0.0f);
  shared_ptr<ColorComponent> colour = make_shared<ColorComponent>(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
  shared_ptr<TileComponent> tile = make_shared<TileComponent>(false);

  Entity e;
  e.setComponent<SpriteComponent>(sprite);
  e.setComponent<TransformComponent>(transform);
  e.setComponent<ColorComponent>(colour);
  e.setComponent<TileComponent>(tile);
  return e;
}