#include "movement_system.hpp"

MovementSystem::MovementSystem()
{
}

MovementSystem::~MovementSystem()
{
}

// TODO: Call this from the constructor instead.
// Call from world to define the size of the screen.
void MovementSystem::setScreenInfo(glm::vec2 info)
{
	screenInfo = info;
}

// Grabs the size of the entity via their transform component
glm::vec2 MovementSystem::getEntitySize(TransformComponent * transformComponent)
{
	return transformComponent->size;
}

// Perform movement on all entities with the movement component.
void MovementSystem::moveEntities(std::vector<Entity> &entities, float dt) {
	//std::cout << dt << "\n";
	for (Entity &e : entities) {
		//SpriteComponent *spriteComponent = e.getComponent<SpriteComponent>();
		TransformComponent *transformComponent = e.getComponent<TransformComponent>();
		MovementComponent *movementComponent = e.getComponent<MovementComponent>();

		if (transformComponent != nullptr && movementComponent != nullptr) {
			// Update velocity
			movementComponent->updateVelocity(dt);
			glm::vec2 velocity = movementComponent->m_velocity;
			glm::vec2 accel = movementComponent->m_accel;

			// Update position
			transformComponent->position += velocity * (dt);
			//TODO: Check & handle offScreenOK.

			glm::vec2 entitySize = getEntitySize(transformComponent);

			if (!movementComponent->m_offScreenOK)
			{
				//Right side of screen
				std::cout << transformComponent->position.x << std::endl;
				if (transformComponent->position.x + entitySize.x > screenInfo.x)
				{
					transformComponent->position.x = screenInfo.x - entitySize.x;
					movementComponent->m_velocity = glm::vec2(0, velocity.y);
					movementComponent->m_accel = glm::vec2(0, accel.y);
				}
				//Left side
				else if (transformComponent->position.x < 0)
				{
					transformComponent->position.x = 0;
					movementComponent->m_velocity = glm::vec2(0, velocity.y);
					movementComponent->m_accel = glm::vec2(0, accel.y);
				}

				//Bottom side
				if (transformComponent->position.y + entitySize.y > screenInfo.y)
				{
					transformComponent->position.y = screenInfo.y - entitySize.y;
					movementComponent->m_velocity = glm::vec2(velocity.x, 0);
					movementComponent->m_accel = glm::vec2(accel.x, 0);
				}
				//Top side
				else if (transformComponent->position.y < 0)
				{
					transformComponent->position.y = 0;
					movementComponent->m_velocity = glm::vec2(velocity.x, 0);
				}
			}
		}
	}
}

