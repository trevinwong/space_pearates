#include "death_system.hpp"

void DeathSystem::handleDeaths(EntityManager &entityManager)
{
	vector<shared_ptr<Entity>> dead = entityManager.getEntities(entityManager.getComponentChecker(vector<int> { ComponentType::death });
	for (shared_ptr<Entity> e : dead) {
		TransformComponent *transform = e->getComponent<TransformComponent>();
		EnemyComponent *enemy = e->getComponent<EnemyComponent>();	

		if (enemy != nullptr) {
			for (int i = 0; i < enemy->worth; i++) {
				entityManager.addEntity(ResourceFactory::build(transform->position, vec2(16, 16)));
			}
		}

	}
}
