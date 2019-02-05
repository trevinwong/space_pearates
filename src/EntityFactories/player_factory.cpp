#include "player_factory.hpp"

PlayerFactory::PlayerFactory()
{
}

PlayerFactory::~PlayerFactory()
{
}

// Generate the player entity
Entity PlayerFactory::build()
{
	Entity e;
	Program *program = new Program(shader_path("sprite.vert"), shader_path("sprite.frag"));
	Texture *texture = new Texture(texture_path("turtle.png"), true);
	SpriteComponent *spriteComponent = new SpriteComponent(program, texture);
	ColorComponent *colorComponent = new ColorComponent(glm::vec4(0.5f, 0.8f, 0.5f, 1.0f));
	MovementComponent *movementComponent = new MovementComponent(glm::vec2(0, 0), glm::vec2(0.5f, 0.8f));
	PlayerComponent *playerComponent = new PlayerComponent();

  glm::vec2 translate = glm::vec2(200.0f, 200.0f);
  glm::vec2 scale = glm::vec2(50.0f, 40.0f);
  GLfloat rotate = 0.0f;
  TransformComponent *transformComponent = new TransformComponent(translate, scale, rotate);
  CollisionComponent *collisionComponent = new CollisionComponent(translate, scale, rotate);

	e.setComponent<SpriteComponent>(spriteComponent);
	e.setComponent<TransformComponent>(transformComponent);
  e.setComponent<CollisionComponent>(collisionComponent);
	e.setComponent<ColorComponent>(colorComponent);
	e.setComponent<MovementComponent>(movementComponent);
	e.setComponent<PlayerComponent>(playerComponent);
	return e;
}
