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
	TransformComponent *transformComponent = new TransformComponent(glm::vec2(200.0f, 200.0f), glm::vec2(50.0f, 40.0f), 0.0f);
	ColorComponent *colorComponent = new ColorComponent(glm::vec4(0.5f, 0.8f, 0.5f, 1.0f));
	MovementComponent *movementComponent = new MovementComponent(glm::vec2(0, 0), glm::vec2(0.5f, 0.8f));
	PlayerComponent *playerComponent = new PlayerComponent();
	e.setComponent<SpriteComponent>(spriteComponent);
	e.setComponent<TransformComponent>(transformComponent);
	e.setComponent<ColorComponent>(colorComponent);
	e.setComponent<MovementComponent>(movementComponent);
	e.setComponent<PlayerComponent>(playerComponent);
	return e;
}
