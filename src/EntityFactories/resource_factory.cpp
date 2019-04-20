#include "resource_factory.hpp"

Entity ResourceFactory::build(vec2 position, float scale)
{
	scale = scale * SCALING_FACTOR;
  shared_ptr<Program> program = make_shared<Program>(shader_path("sprite.vert"), shader_path("sprite.frag"));
  shared_ptr<Texture> texture = make_shared<Texture>(texture_path("coin_rotating.png"), true);

  shared_ptr<SpriteComponent> sprite = make_shared<SpriteComponent>(program, texture);
  shared_ptr<ColorComponent> colour = make_shared<ColorComponent>(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
  shared_ptr<AnimatedComponent> animated = make_shared<AnimatedComponent>(6, 0.2);

  shared_ptr<ResourceComponent> resource = make_shared<ResourceComponent>(20.0); // resource stays on screen for 20s
  shared_ptr<MovementComponent> movement = make_shared<MovementComponent>(
    vec2(0.0f, 0.0f), vec2(0.0f, 0.0f), vec2(0.0f, GRAVITY_VELOCITY), vec2(0.0f, GRAVITY_ACCEL));

  shared_ptr<TransformComponent> transform = make_shared<TransformComponent>(position, scale, 0.0f);
  shared_ptr<CollisionComponent> collision = make_shared<CollisionComponent>(position, scale, 0.0f);

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

vector<Entity> ResourceFactory::buildCluster(int amount, vec2 position, vec2 size)
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
    cluster.push_back(ResourceFactory::build(randPos));
  }
  return cluster;
}


void ResourceFactory::spawnInitial(EntityManager & entities, vec2 location)
{
  vec2 position = location + vec2(-60.0f, -60.0f);
  for (int i = 0; i < 4; i++) {
    entities.addEntity(build(position));
    position.x += 60.0f;
  }
}
