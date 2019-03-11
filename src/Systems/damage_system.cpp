#include "damage_system.hpp"

void DamageSystem::handleDamage(EntityManager &entityManager)
{
  vector<shared_ptr<Entity>> damaged = entityManager.getEntities(entityManager.getComponentChecker(vector<int>{ ComponentType::damage }));

  for (shared_ptr<Entity> e : damaged) {
    DamageComponent *damage = e->getComponent<DamageComponent>();
    HealthComponent *health = e->getComponent<HealthComponent>();

    if (health != nullptr) {
      health->curHP -= damage->power;
      if (health->curHP <= 0) {
        e->setComponent<DeathComponent>(new DeathComponent());
      }
      else {
        e->removeComponent<DamageComponent>();
      }
    }
  }
}
