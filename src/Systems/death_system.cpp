#include "death_system.hpp"

void DeathSystem::handleDeaths(EntityManager &entityManager)
{
	vector<shared_ptr<Entity>> dead = entityManager.getEntities(entityManager.getComponentChecker(vector<int> { ComponentType::death }));
	for (shared_ptr<Entity> e : dead) {
		TransformComponent *transform = e->getComponent<TransformComponent>();
		EnemyComponent *enemy = e->getComponent<EnemyComponent>();	
		ProjectileComponent *projectile = e->getComponent<ProjectileComponent>();

		if (enemy != nullptr) {
			for (Entity resource : ResourceFactory::buildCluster(enemy->worth, transform->position, transform->size)) {;
				entityManager.addEntity(resource);
			}
			entityManager.removeEntity(e);
		}

		if (projectile != nullptr) {
			entityManager.removeEntity(e);
		}

	}
}
