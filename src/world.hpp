#ifndef WORLD_H
#define WORLD_H

#include "utility.hpp"
#include "entity_manager.hpp"
#include "sprite_system.hpp"

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
};

#endif
