#include "resource_factory.hpp"

Entity ResourceFactory::build(vec2 position, float scale)
{
  Program *program = new Program(shader_path("sprite.vert"), shader_path("sprite.frag"));
  Texture *texture = new Texture(texture_path("coin_rotating.png"), true);

  SpriteComponent *sprite = new SpriteComponent(program, texture);
  ColorComponent *colour = new ColorComponent(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
  AnimatedComponent *animated = new AnimatedComponent(6, 0.2);

  ResourceComponent *resource = new ResourceComponent(20.0); // resource stays on screen for 20s
  MovementComponent *movement = new MovementComponent(
    vec2(0.0f, 0.0f), vec2(0.0f, 0.0f), vec2(0.0f, 50.0f), vec2(0.0f, 50.0f));

  TransformComponent *transform = new TransformComponent(position, scale, 0.0f);
  CollisionComponent *collision = new CollisionComponent(position, scale, 0.0f);

  Entity e;
  e.setComponent<SpriteComponent>(sprite);
  e.setComponent<ColorComponent>(colour);
  e.setComponent<AnimatedComponent>(animated);
  e.setComponent<ResourceComponent>(resource);
  e.setComponent<MovementComponent>(movement);
  e.setComponent<TransformComponent>(transform);
  e.setComponent<CollisionComponent>(collision);
  return e;
}

// Just for lazy testing.. spawns some coins along the floor, hardcoded
void ResourceFactory::spawnMany(EntityManager & entities)
{
  vec2 position = vec2(SCREEN_WIDTH/4, 550);
  for (int i = 0; i < 6; i++) {
    entities.addEntity(build(position));
    position.x += SCREEN_WIDTH/12;
  }
}
