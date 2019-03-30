#include "player_system.hpp"

void PlayerSystem::interpInput(EntityManager &entityManager, float dt, GLboolean keys[], GLboolean keysProcessed[])
{
	vector<shared_ptr<Entity>> entities = entityManager.getEntities(entityManager.getComponentChecker(vector<int>{ComponentType::player, ComponentType::movement}));

	for (shared_ptr<Entity> e : entities) {
		shared_ptr<PlayerComponent> player = e->getComponent<PlayerComponent>();
		shared_ptr<MovementComponent> movement = e->getComponent<MovementComponent>();
		shared_ptr<SpriteComponent> sprite = e->getComponent<SpriteComponent>();

		vec2 newAcceleration = movement->accel;
		vec2 newVelocity = movement->velocity;

		if (keys[GLFW_KEY_LEFT])
		{
			sprite->texture = player->texture_left;

			if (newAcceleration.x > 0) newAcceleration.x = 0;
			newAcceleration.x -= movement->maxAccel.x * 0.8;
			if (newVelocity.x > 0) newVelocity.x -= movement->maxVelocity.x * 0.2;
		}
		else if (keys[GLFW_KEY_RIGHT])
		{
			sprite->texture = player->texture_right;

			if (newAcceleration.x < 0) newAcceleration.x = 0;
			newAcceleration.x += movement->maxAccel.x * 0.8;
			if (newVelocity.x < 0) newVelocity.x += movement->maxVelocity.x * 0.2;
		}

		if (keys[GLFW_KEY_UP] && !keysProcessed[GLFW_KEY_UP] && player->jumps > 0)
		{
			Mix_PlayChannel(-1, AudioLoader::getInstance().jump, 0);
			keysProcessed[GLFW_KEY_UP] = true;
			player->jumps--;
			if (newVelocity.y > 0) newVelocity.y = 0;
			newVelocity.y += player->jumpVelocity;
		}
		else if (keys[GLFW_KEY_DOWN])
		{
		}

		else {
			if (movement->velocity.x == 0) {
				sprite->texture = player->texture_idle;
			}
		}

		movement->accel = newAcceleration;
		movement->velocity = newVelocity;
	}
}
