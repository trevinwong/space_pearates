#include "death_system.hpp"

void DeathSystem::handleEnemyDeath(EntityManager &entityManager, shared_ptr<Entity> enemy)
{
    shared_ptr<TransformComponent> transform = enemy->getComponent<TransformComponent>();
		shared_ptr<EnemyComponent> enemyData = enemy->getComponent<EnemyComponent>();
		if (transform != nullptr) {
			for (Entity resource : ResourceFactory::buildCluster(enemyData->worth, transform->position, transform->size)) {
				if (rand() % 100 >= (100 - dropRate))
				{
					entityManager.addEntity(resource);
				}
				
			}
			entityManager.removeEntity(enemy);
			WavesetSystem::getInstance().decrementEnemies(1, entityManager);
			ParticleSystem::emitParticleCluster(entityManager, transform->position);
			Mix_PlayChannel(-1, AudioLoader::getInstance().enemy_dead, 0);
		}
}

void DeathSystem::handleProjectileDeath(EntityManager &entityManager, shared_ptr<Entity> projectile)
{
	entityManager.removeEntity(projectile);
}

void DeathSystem::handlePlayerDeath(EntityManager &entityManager, shared_ptr<Entity> player)
{
	HUD::getInstance().game_over = true;
}

void DeathSystem::handleDeaths(EntityManager &entityManager)
{
	vector<shared_ptr<Entity>> dead = entityManager.getEntities(entityManager.getComponentChecker(vector<int>{ ComponentType::death }));
	for (shared_ptr<Entity> e : dead) {
		shared_ptr<EnemyComponent> enemy = e->getComponent<EnemyComponent>();
		shared_ptr<PlayerComponent> player = e->getComponent<PlayerComponent>();
		shared_ptr<ProjectileComponent> projectile = e->getComponent<ProjectileComponent>();

		if (enemy != nullptr) handleEnemyDeath(entityManager, e);
		if (player != nullptr) handlePlayerDeath(entityManager, e);
		if (projectile != nullptr) handleProjectileDeath(entityManager, e);
	}
}
