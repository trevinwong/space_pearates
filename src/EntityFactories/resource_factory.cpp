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

vector<Entity> ResourceFactory::buildCluster(int amount, vec2 position, vec2 size, float scale)
{
  float CLUSTER_OFFSET_X = size.x;
  float CLUSTER_OFFSET_Y = size.y / 2;
  vector<Entity> cluster;
  std::random_device rd;
  std::mt19937 gen(rd());
  for (int i = 0; i < amount; i++) {
    float minY = position.y;
    float maxY = position.y + CLUSTER_OFFSET_Y;
    float minX = position.x;
    float maxX = position.x + CLUSTER_OFFSET_X;

    std::uniform_real_distribution<> disX(minX, maxX);
    std::uniform_real_distribution<> disY(minY, maxY);
    vec2 randPos = { disX(gen), disY(gen) };
    cluster.push_back(ResourceFactory::build(randPos, scale));
  }
  return cluster;
}


// Just for lazy testing.. spawns some coins along the floor, hardcoded
void ResourceFactory::spawnInitial(EntityManager & entities)
{
  vec2 position = vec2(SCREEN_WIDTH / 4, SCREEN_HEIGHT - 200.0f);
  for (int i = 0; i < 6; i++) {
    entities.addEntity(build(position));
    position.x += SCREEN_WIDTH / 11;
  }
}
