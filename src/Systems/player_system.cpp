#include "player_system.hpp"

PlayerSystem::PlayerSystem()
{
}

PlayerSystem::~PlayerSystem()
{
}

// Perform actions on the player entity based on the user's inputs.
void PlayerSystem::interpInput(vector<shared_ptr<Entity>> entities, GLboolean keys[])
{
	for (shared_ptr<Entity> e : entities) {
		MovementComponent *movementComponent = e->getComponent<MovementComponent>();
		PlayerComponent * playerComponent = e->getComponent<PlayerComponent>();


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
				stopMovingX(movementComponent);
			}

			//Check for vertical movement.
			if (keys[GLFW_KEY_UP])
			{
				moveUp(movementComponent);
			}
			else if (keys[GLFW_KEY_DOWN])
			{
				moveDown(movementComponent);
			}
			else if (!keys[GLFW_KEY_UP] && !keys[GLFW_KEY_DOWN])
			{
				stopMovingY(movementComponent);
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

void PlayerSystem::moveUp(MovementComponent* mvComp)
{
	mvComp->setAcceleration(glm::vec2(0, -walkAccelSpeed));
}

void PlayerSystem::moveDown(MovementComponent* mvComp)
{
	mvComp->setAcceleration(glm::vec2(0, walkAccelSpeed));
}

void PlayerSystem::stopMovingX(MovementComponent * mvComp)
{
	mvComp->setVelocity(glm::vec2(0, mvComp->m_velocity.y));
	mvComp->setAcceleration(glm::vec2(0, mvComp->m_accel.y));
}

void PlayerSystem::stopMovingY(MovementComponent * mvComp)
{
	mvComp->setVelocity(glm::vec2(mvComp->m_velocity.x, 0));
	mvComp->setAcceleration(glm::vec2(mvComp->m_accel.x, 0));
}
