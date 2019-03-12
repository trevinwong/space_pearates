#include "death_system.hpp"

void DeathSystem::handleDeaths(EntityManager &entityManager)
{
	vector<shared_ptr<Entity>> dead = entityManager.getEntities(entityManager.getComponentChecker(vector<int>{ ComponentType::death }));
	for (shared_ptr<Entity> e : dead) {

		TransformComponent *transform = e->getComponent<TransformComponent>();
		EnemyComponent *enemy = e->getComponent<EnemyComponent>();
		if (enemy != nullptr && transform != nullptr) {
			for (Entity resource : ResourceFactory::buildCluster(enemy->worth, transform->position, transform->size)) {
				if (rand() % 100 >= dropRate)
				{
					entityManager.addEntity(resource);
				}
				
			}
			entityManager.removeEntity(e);
			WavesetSystem::getInstance().decrementEnemies(1, entityManager);
			ParticleSystem::emitParticleCluster(entityManager, transform->position);
			Mix_PlayChannel(-1, AudioLoader::getInstance().enemy_dead, 0);
		}

		ProjectileComponent *projectile = e->getComponent<ProjectileComponent>();
		if (projectile != nullptr) {
			entityManager.removeEntity(e);
		}
	}
}
