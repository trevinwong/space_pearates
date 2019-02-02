#include "player_system.hpp"

PlayerSystem::PlayerSystem()
{
}

PlayerSystem::~PlayerSystem()
{
}

// Perform actions on the player entity based on the user's inputs.
void PlayerSystem::interpInput(std::vector<Entity> &entities, GLboolean keys[])
{
	for (Entity &e : entities) {
		MovementComponent *movementComponent = e.getComponent<MovementComponent>();
		PlayerComponent * playerComponent = e.getComponent<PlayerComponent>();


		if (movementComponent != nullptr && playerComponent != nullptr) 
		{
			// Check for keys being pressed.
			if (keys[GLFW_KEY_LEFT])
			{
				walkLeft(movementComponent);
			}
			else if (keys[GLFW_KEY_RIGHT])
			{
				walkRight(movementComponent);
			}
			else if (!keys[GLFW_KEY_RIGHT] && !keys[GLFW_KEY_LEFT])
			{
				stopMoving(movementComponent);
			}
		}
	}
}

void PlayerSystem::walkRight(MovementComponent * mvComp)
{
	mvComp->setAcceleration(glm::vec2(walkAccelSpeed, 0));
}

void PlayerSystem::walkLeft(MovementComponent* mvComp)
{
	mvComp->setAcceleration(glm::vec2(-walkAccelSpeed, 0));
}

void PlayerSystem::stopMoving(MovementComponent * mvComp)
{
	mvComp->setVelocity(glm::vec2(0, 0));
	mvComp->setAcceleration(glm::vec2(0, 0));
}
