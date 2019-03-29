#include "enemy_factory.hpp"

Entity EnemyFactory::build(vec2 position, vec2 velocity, int hpMult, int spdMult, int atkMult, int type, vec2 scale)
{
	float speed = spdMult / 100;
	float hp = hpMult / 100;
	float attack = atkMult / 100;
  shared_ptr<Program> program = make_shared<Program>(shader_path("sprite.vert"), shader_path("sprite.frag"));
  shared_ptr<Texture> texture = make_shared<Texture>(texture_path("enemy0.png"), true);
  shared_ptr<SpriteComponent> sprite = make_shared<SpriteComponent>(program, texture);
  shared_ptr<TransformComponent> transform = make_shared<TransformComponent>(position, scale, 0.0f);
  shared_ptr<EnemyPathComponent> pathfind = make_shared<EnemyPathComponent>(type);
  shared_ptr<CollisionComponent> collision = make_shared<CollisionComponent>(position, scale, 0.0f);
  shared_ptr<MovementComponent> move = make_shared<MovementComponent>(velocity, vec2(0.0, 0.0), speed * vec2(40.0f, 40.0f), vec2(0.f, 0.f));
  shared_ptr<ColorComponent> colour = make_shared<ColorComponent>(glm::vec4(0.0f, 1.0f, 0.6f, 1.0f));
  shared_ptr<Program> billboardProgram = make_shared<Program>(shader_path("billboard.vert"), shader_path("billboard.frag"));
  shared_ptr<HealthComponent> health = make_shared<HealthComponent>(billboardProgram, 30 * hp);
  shared_ptr<EnemyComponent> enemy = make_shared<EnemyComponent>(1, attack);
  shared_ptr<WaterTowerFactorComponent> waterTowerFactor = make_shared<WaterTowerFactorComponent>();

  Entity e;
  e.setComponent<SpriteComponent>(sprite);
  e.setComponent<TransformComponent>(transform);
	e.setComponent<CollisionComponent>(collision);
  e.setComponent<ColorComponent>(colour);
  e.setComponent<MovementComponent>(move);
  e.setComponent<WaterTowerFactorComponent>(waterTowerFactor);
  e.setComponent<HealthComponent>(health);
  e.setComponent<EnemyComponent>(enemy);
  e.setComponent<EnemyPathComponent>(pathfind);

  return e;
}
