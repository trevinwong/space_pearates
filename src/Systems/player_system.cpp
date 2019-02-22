#include "player_system.hpp"

void PlayerSystem::interpInput(EntityManager &entityManager, float dt, GLboolean keys[], GLboolean keysProcessed[])
{
	vector<shared_ptr<Entity>> entities = entityManager.getEntities(entityManager.getComponentChecker(vector<int>{ComponentType::player, ComponentType::movement}));

	for (shared_ptr<Entity> e : entities) {
		PlayerComponent *player = e->getComponent<PlayerComponent>();
		MovementComponent *movement = e->getComponent<MovementComponent>();
		vec2 newAcceleration = movement->accel;
		vec2 newVelocity = movement->velocity;

		if (keys[GLFW_KEY_LEFT])
		{
			if (newAcceleration.x > 0) newAcceleration.x = 0;
			if (newVelocity.x > 0) newVelocity.x -= movement->maxVelocity.x * 0.1;
			newAcceleration.x -= movement->maxAccel.x * 0.8;
		}
		else if (keys[GLFW_KEY_RIGHT])
		{
			if (newAcceleration.x < 0) newAcceleration.x = 0;
			newAcceleration.x += movement->maxAccel.x * 0.8;
			if (newVelocity.x < 0) newVelocity.x += movement->maxVelocity.x * 0.1;
		}

		if (keys[GLFW_KEY_UP] && !keysProcessed[GLFW_KEY_UP] && player->jumps > 0)
		{
			keysProcessed[GLFW_KEY_UP] = true;
			player->jumps--;
			if (movement->velocity.y > 0) movement->velocity.y = 0;
			newVelocity.y += player->jumpVelocity;
		}
		else if (keys[GLFW_KEY_DOWN])
		{
		}

		movement->accel = newAcceleration;
		movement->velocity = newVelocity;
	}
}
