#include "movement_system.hpp"

MovementSystem::MovementSystem()
{
}

MovementSystem::~MovementSystem()
{
}

void MovementSystem::moveEntities(std::vector<Entity> &entities) {

	for (Entity &e : entities) {
		//SpriteComponent *spriteComponent = e.getComponent<SpriteComponent>();
		TransformComponent *transformComponent = e.getComponent<TransformComponent>();
		MovementComponent *movementComponent = e.getComponent<MovementComponent>();

		if (transformComponent != nullptr && movementComponent != nullptr) {
			// Update velocity
			movementComponent->updateVelocity();
			glm::vec2 velocity = movementComponent->m_velocity;

			// Update position
			transformComponent->position += velocity;
			//TODO: Check & handle offScreenOK.
		}
	}
}

void MovementSystem::processEvent(Event * event)
{
  cout << "PROCESS MEEee " << event->getTypeId() << endl;
}

