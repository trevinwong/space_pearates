#include "player_system.hpp"

void PlayerSystem::interpInput(EntityManager &entityManager, float dt, GLboolean keys[], GLboolean keysProcessed[])
{
	vector<shared_ptr<Entity>> players = entityManager.getEntities(entityManager.getComponentChecker(vector<int>{ComponentType::player}));

  for (shared_ptr<Entity> player : players) {
		shared_ptr<PlayerComponent> playerComponent = player->getComponent<PlayerComponent>();
    if (playerComponent->movementState == PlayerMovementState::NEUTRAL) {
      handleActionsInNeutral(player, dt, keys, keysProcessed);
    }
    if (playerComponent->movementState == PlayerMovementState::HITSTUN) {
      handleActionsInHitstun(player, dt, keys, keysProcessed);
    } 
  }   
}

bool PlayerSystem::outOfBoundsFailsafe(shared_ptr<Entity> player)
{
	shared_ptr<TransformComponent> transform = player->getComponent<TransformComponent>();
	if (transform->position.y > SCREEN_HEIGHT)
	{
		transform->position.y = 0;
		return true;
	}
	if (transform->position.x > SCREEN_WIDTH || transform->position.x < 0)
	{
		transform->position.x = SCREEN_WIDTH/2;
		return true;
	}
	return false;
}


void PlayerSystem::handleActionsInNeutral(shared_ptr<Entity> player, float dt, GLboolean keys[], GLboolean keysProcessed[])
{
  shared_ptr<PlayerComponent> playerComponent = player->getComponent<PlayerComponent>();
  shared_ptr<MovementComponent> movement = player->getComponent<MovementComponent>();
  shared_ptr<SpriteComponent> sprite = player->getComponent<SpriteComponent>();

  vec2 newAcceleration = movement->accel;
  vec2 newVelocity = movement->velocity;

  if (keys[GLFW_KEY_LEFT])
  {
    sprite->texture = playerComponent->texture_left;

    if (newAcceleration.x > 0) newAcceleration.x = 0;
    newAcceleration.x -= movement->maxAccel.x * 0.8;
    if (newVelocity.x > 0) newVelocity.x -= movement->maxVelocity.x * 0.2;
  }
  else if (keys[GLFW_KEY_RIGHT])
  {
    sprite->texture = playerComponent->texture_right;

    if (newAcceleration.x < 0) newAcceleration.x = 0;
    newAcceleration.x += movement->maxAccel.x * 0.8;
    if (newVelocity.x < 0) newVelocity.x += movement->maxVelocity.x * 0.2;
  }

  if (keys[GLFW_KEY_UP] && !keysProcessed[GLFW_KEY_UP] && playerComponent->jumps > 0)
  {
    Mix_PlayChannel(-1, AudioLoader::getInstance().jump, 0);
    keysProcessed[GLFW_KEY_UP] = true;
    playerComponent->jumps--;
    if (newVelocity.y > 0) newVelocity.y = 0;
    newVelocity.y += playerComponent->jumpVelocity;
  }
  else if (keys[GLFW_KEY_DOWN])
  {
  }

  else {
    if (movement->velocity.x == 0) {
      sprite->texture = playerComponent->texture_idle;
    }
  }
  outOfBoundsFailsafe(player);
  movement->accel = newAcceleration;
  movement->velocity = newVelocity;
}

void PlayerSystem::handleActionsInHitstun(shared_ptr<Entity> player, float dt, GLboolean keys[], GLboolean keysProcessed[])
{
  shared_ptr<PlayerComponent> playerComponent = player->getComponent<PlayerComponent>();
  playerComponent->movementStateDuration.update(dt);
  if (playerComponent->movementStateDuration.getTimeLeft() <= 0) {
    playerComponent->movementState = PlayerMovementState::NEUTRAL;
  }
}
