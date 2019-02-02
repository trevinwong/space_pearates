#include "movement_system.hpp"
#include "movement_component.hpp"

MovementSystem::MovementSystem()
{
}

MovementSystem::~MovementSystem()
{
}

void MovementSystem::moveEntities(std::vector<Entity> &entities) {

	for (Entity &e : entities) {
		printf("%d\n", e.id);
		//SpriteComponent *spriteComponent = e.getComponent<SpriteComponent>();
		TransformComponent *transformComponent = e.getComponent<TransformComponent>();
		MovementComponent *movementComponent = e.getComponent<MovementComponent>();

		printf("xxxxxxxx\n");
		if (transformComponent != nullptr && movementComponent != nullptr) {
			printf("1223\n");
			// Update velocity
			movementComponent->updateVelocity();
			glm::vec2 velocity = movementComponent->m_velocity;
			printf("xxxxxxxx\n");

			// Update position
			transformComponent->position += velocity;
			//TODO: Check & handle offScreenOK.
		}
	}
}

