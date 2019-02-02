#ifndef WORLD_H
#define WORLD_H

#include "utility.hpp"
#include "entity_manager.hpp"
#include "sprite_system.hpp"
<<<<<<< HEAD
#include "TileMapping/tile_map_system.hpp"
#include "Enemies/enemy.hpp"
=======
#include "movement_system.hpp"
#include "TileMapping/tile_map_system.hpp"
#include "TileMapping/map_entity_factory.hpp"
>>>>>>> d34d243b4fe2ea985337ea47634c292a495c6e88


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
<<<<<<< HEAD
	//Change later after figuring out how to read multiple enemies
	Enemy enemy;
=======
	MovementSystem movementSystem;
>>>>>>> d34d243b4fe2ea985337ea47634c292a495c6e88
};

#endif
