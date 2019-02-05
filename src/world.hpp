#ifndef WORLD_H
#define WORLD_H

#include "Enemies/enemy.hpp"
#include "utility.hpp"
#include "entity_manager.hpp"
#include "TileMapping/tile_map_system.hpp"
#include "TileMapping/map_entity_factory.hpp"
#include "Systems/sprite_system.hpp"
#include "Systems/movement_system.hpp"
#include "Systems/player_system.hpp"
#include "Systems/collision_system.hpp"
#include "EntityFactories/player_factory.hpp"



// TO-DO: Look into replacing Keys array with direct callback.
// TO-DO: Look into replacing processInput with direct callback.
// TO-DO: Look into not having to include every component file.
class World
{
public:
	World();
	~World();
	void init(glm::vec2 screen);
	void update(float dt); // dt = delta time, how much time has passed since update was last called
	void processInput(float dt);
	void draw();
	void destroy();
	GLboolean keys[1024];
	GLboolean keysProcessed[1024];
private:
	EntityManager entityManager;
	SpriteSystem spriteSystem;
	glm::mat4 projection;
	TileMapSystem tileMapSystem;
	//Change later after figuring out how to read multiple enemies
	Enemy enemy;
	MovementSystem movementSystem;
	PlayerSystem playerSystem;
  CollisionSystem collisionSystem;
};

#endif
