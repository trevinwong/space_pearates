#include "state_system.hpp"

void StateSystem::handleStateChanges(EntityManager &entityManager, float dt)
{
	vector<shared_ptr<Entity>> players = entityManager.getEntities(entityManager.getComponentChecker(vector<int>{ ComponentType::player }));

	for (shared_ptr<Entity> player : players) {
    handlePlayerState(player, dt);
	}
}

void StateSystem::handlePlayerState(shared_ptr<Entity> player, float dt)
{
     shared_ptr<PlayerComponent> playerComponent = player->getComponent<PlayerComponent>();                                                              
     shared_ptr<ColorComponent> color = player->getComponent<ColorComponent>();
     shared_ptr<SpriteComponent> sprite = player->getComponent<SpriteComponent>();

     playerComponent->healthStateDuration.update(dt);                            
     if (playerComponent->healthStateDuration.getTimeLeft() <= 0) {              
       shared_ptr<TransformComponent> transform = player->getComponent<TransformComponent>();
       playerComponent->healthState = PlayerHealthState::VULNERABLE;
       color->RGBA.w = 1.0f;
     } else {
       float FADE_ALPHA = 0.4f;
       sprite->blinkTimer.update(dt);
       if (sprite->blinkTimer.getTimeLeft() <= 0) {
         sprite->blinkTimer.reset();
         color->RGBA.w = (color->RGBA.w == FADE_ALPHA) ? 1.0f : FADE_ALPHA;
       }
     }

}
