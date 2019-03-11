#include "player_factory.hpp"

Entity PlayerFactory::build(vec2 translation, vec2 scale)
{
  Program *program = new Program(shader_path("sprite.vert"), shader_path("sprite.frag"));
  Texture *texture = new Texture(texture_path("player.png"), true);

  SpriteComponent *sprite = new SpriteComponent(program, texture);
  ColorComponent *color = new ColorComponent(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
  AnimatedComponent *animated = new AnimatedComponent(5, 0.2);

  PlayerComponent *player = new PlayerComponent();
  MovementComponent *movement = new MovementComponent(
    vec2(0.0f, 0.0f), vec2(0.0f, 0.0f), vec2(300.0f, 350.0f), vec2(1000.0f, 600.0f));
  movement->offScreenOK = false;

  Program *billboardProgram = new Program(shader_path("billboard.vert"), shader_path("billboard.frag"));
  HealthComponent *health = new HealthComponent(billboardProgram, 30);
  GLfloat rotation = 0.0f;
  TransformComponent *transform = new TransformComponent(translation, scale, rotation);
  CollisionComponent *collision = new CollisionComponent(translation, scale, rotation);

  WalletComponent *wallet = new WalletComponent();

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
