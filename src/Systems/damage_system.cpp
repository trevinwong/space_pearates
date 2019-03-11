#include "damage_system.hpp"

void DamageSystem::handleDamage(EntityManager &entityManager)
{
  vector<shared_ptr<Entity>> damaged = entityManager.getEntities(entityManager.getComponentChecker(vector<int>{ ComponentType::damage }));

  for (shared_ptr<Entity> e : damaged) {
    shared_ptr<DamageComponent> damage = e->getComponent<DamageComponent>();
    shared_ptr<HealthComponent> health = e->getComponent<HealthComponent>();
		shared_ptr<PlayerComponent> player = e->getComponent<PlayerComponent>();

    if (health != nullptr) {
      health->curHP -= damage->power;
      if (health->curHP <= 0) {
        e->setComponent<DeathComponent>(make_shared<DeathComponent>());
				// TODO: add a base component here and change subi's hardcoded monkey code in enemySystem
				if (player)
					HUD::getInstance().game_over = true;
      }
      else {
        e->removeComponent<DamageComponent>();
      }
    }
  }
}
