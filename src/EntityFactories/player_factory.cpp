#include "player_factory.hpp"

Entity PlayerFactory::build(vec2 translation)
{
  shared_ptr<Program> program = make_shared<Program>(shader_path("sprite.vert"), shader_path("sprite.frag"));
  shared_ptr<Texture> texture = make_shared<Texture>(texture_path("player.png"), true);

  shared_ptr<SpriteComponent> sprite = make_shared<SpriteComponent>(program, texture);
  shared_ptr<ColorComponent> color = make_shared<ColorComponent>(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
  shared_ptr<AnimatedComponent> animated = make_shared<AnimatedComponent>(5, 0.2);

  shared_ptr<PlayerComponent> player = make_shared<PlayerComponent>(PlayerDataLoader::playerData.maxJumps, PlayerDataLoader::playerData.jumpVelocity);
  shared_ptr<MovementComponent> movement = make_shared<MovementComponent>(
    vec2(0.0f, 0.0f), vec2(0.0f, 0.0f), PlayerDataLoader::playerData.maxVelocity, PlayerDataLoader::playerData.maxAccel);
  movement->offScreenOK = false;

	shared_ptr<Program> billboardProgram = make_shared<Program>(shader_path("billboard.vert"), shader_path("billboard.frag"));
  shared_ptr<HealthComponent> health = make_shared<HealthComponent>(billboardProgram, PlayerDataLoader::playerData.health);
  GLfloat rotation = 0.0f;
  shared_ptr<TransformComponent> transform = make_shared<TransformComponent>(translation, PlayerDataLoader::playerData.size  * SCALING_FACTOR, rotation);
  shared_ptr<CollisionComponent> collision = make_shared<CollisionComponent>(translation, PlayerDataLoader::playerData.size  * SCALING_FACTOR, rotation);

  shared_ptr<WalletComponent> wallet = make_shared<WalletComponent>(2);

  Entity e;
  e.setComponent<SpriteComponent>(sprite);
  e.setComponent<ColorComponent>(color);
  e.setComponent<AnimatedComponent>(animated);
  e.setComponent<PlayerComponent>(player);
  e.setComponent<HealthComponent>(health);
  e.setComponent<MovementComponent>(movement);
  e.setComponent<TransformComponent>(transform);
  e.setComponent<CollisionComponent>(collision);
  e.setComponent<WalletComponent>(wallet);
  return e;
}
