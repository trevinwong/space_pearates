#include "world.hpp"

// World class constructor is to set up data structures that will persist through multiple restarts.
World::World()
{
	spriteSystem = SpriteSystem();
	tileMapSystem = TileMapSystem();
	movementSystem = MovementSystem();
}

World::~World()
{
}

// Data structures that should be re-initialized every restart of the world should be placed here.
void World::init(glm::vec2 screen)
{
	projection = glm::ortho(0.0f, static_cast<GLfloat>(screen.x), static_cast<GLfloat>(screen.y), 0.0f, -1.0f, 1.0f);
	entityManager = EntityManager();
	tileMapSystem.loadTileMap(screen, entityManager); // Add platform tiles

	Entity e;
	Program *program = new Program(shader_path("sprite.vert"), shader_path("sprite.frag"));
	Texture *texture = new Texture(texture_path("turtle.png"), true);
	SpriteComponent *spriteComponent = new SpriteComponent(program, texture);
	TransformComponent *transformComponent = new TransformComponent(glm::vec2(200.0f, 200.0f), glm::vec2(50.0f, 40.0f), 0.0f);
	ColorComponent *colorComponent = new ColorComponent(glm::vec4(0.5f, 0.8f, 0.5f, 1.0f));
	MovementComponent *movementComponent = new MovementComponent(glm::vec2(0, 0), glm::vec2(0.5f, 0.8f));
	e.setComponent<SpriteComponent>(spriteComponent);
	e.setComponent<TransformComponent>(transformComponent);
	e.setComponent<ColorComponent>(colorComponent);
	e.setComponent<MovementComponent>(movementComponent);
	entityManager.addEntity(e);
}

// dt is known as delta time, how much time has passed since update was last called
void World::update(float dt)
{
	std::vector<Entity> &entities = entityManager.getEntities();
	movementSystem.moveEntities(entities);
}

void World::processInput(float dt)
{

}

void World::draw()
{
  std::vector<Entity> &entities = entityManager.getEntities();
  spriteSystem.drawSprites(entities, projection);
}

// Possibly redundant - destructor can serve the same purpose.
// However, use this function anyways just in-case we need to explicitly call it.
void World::destroy()
{

}




