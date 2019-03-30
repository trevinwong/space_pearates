#include "collision_system.hpp"

void CollisionSystem::setScreenInfo(vec2 _screen)
{
  screen = _screen;
}

EntityGrid CollisionSystem::preprocessEntitiesIntoGrid(vector<shared_ptr<Entity>> entities)
{
  int num_cells_in_row = screen.x / MIN_CELL_SIZE;
  int num_cells_in_col = screen.y / MIN_CELL_SIZE;
  float cell_width = screen.x / num_cells_in_row;
  float cell_height = screen.y / num_cells_in_col;
  EntityGrid grid(num_cells_in_row, vector<vector<shared_ptr<Entity>>>(num_cells_in_col, vector<shared_ptr<Entity>>{}));

  for (int x = 0; x < num_cells_in_row; x++) {
    for (int y = 0; y < num_cells_in_col; y++) {
      vec2 cell_pos = { x * cell_width, y * cell_height };
      vec2 cell_size = { cell_width, cell_height };

      for (shared_ptr<Entity> e : entities) {
				shared_ptr<CollisionComponent> collision = e->getComponent<CollisionComponent>();
        if (Math::isCollidingWith(cell_pos, cell_size, collision->position, collision->size)) {
          grid[x][y].push_back(e);
        }
      }
    }
  }
  return grid;
}

void CollisionSystem::checkCollisions(EntityManager &entityManager)
{
  vector<shared_ptr<Entity>> collidables = entityManager.getEntities(
    entityManager.getComponentChecker(vector<int> {ComponentType::collision}));
  EntityGrid grid = preprocessEntitiesIntoGrid(collidables);
	unordered_map<string, bool> collision_cache;

  for (vector<vector<shared_ptr<Entity>>> row : grid) {
    for (vector<shared_ptr<Entity>> cell : row) {
      for (shared_ptr<Entity> e1 : cell) {
        for (shared_ptr<Entity> e2 : cell) {
					if (e1 != e2) {
						shared_ptr<CollisionComponent> e1_collision = e1->getComponent<CollisionComponent>();
						shared_ptr<CollisionComponent> e2_collision = e2->getComponent<CollisionComponent>();
						string hash1 = std::to_string(e1->id) + ":" + std::to_string(e2->id);
						string hash2 = std::to_string(e2->id) + ":" + std::to_string(e1->id);

						if (e1_collision && e2_collision && e1_collision->isCollidingWith(*e2_collision) && !collision_cache[hash1] && !collision_cache[hash2]) {
							collision_cache[hash1] = true;
							collision_cache[hash2] = true;
							handleCollision(e1, e2, entityManager);
						}
          }
        }
      }
    }
  }
}

void CollisionSystem::handleCollisionOfType(bitset<ComponentType::max_count> components1, bitset<ComponentType::max_count> components2, shared_ptr<Entity> e1, shared_ptr<Entity> e2, EntityManager &entityManager, void(*handleCollisionFn)(shared_ptr<Entity>, shared_ptr<Entity>, EntityManager&))
{
	bool pair1 = e1->hasComponents(components1) && e2->hasComponents(components2);
	bool pair2 = e1->hasComponents(components2) && e2->hasComponents(components1);
	if (pair1) handleCollisionFn(e1, e2, entityManager);
	if (pair2) handleCollisionFn(e2, e1, entityManager);
}

void CollisionSystem::handlePlayerResource(shared_ptr<Entity> player, shared_ptr<Entity> resource, EntityManager &entityManager)
{
	// remove the resouce from world
	entityManager.removeEntity(resource);
	// Add the resource into wallet
	shared_ptr<WalletComponent> wallet = player->getComponent<WalletComponent>();
	if (wallet != nullptr) {
		// TODO: for diff type resources, increase diff amount
		wallet->earn(1);
		// update HUD resource counter
		// TODO: so far only coins, modify this part for diff types of resource
		HUD::getInstance().resource_count = wallet->coins;
	}
	Mix_PlayChannel(-1, AudioLoader::getInstance().collect_coin_sound, 0);
}

void CollisionSystem::handlePlayerEnemy(shared_ptr<Entity> player, shared_ptr<Entity> enemy, EntityManager &entityManager)
{

	player->setComponent<DamageComponent>(make_shared<DamageComponent>(enemy->getComponent<EnemyComponent>()->totalAtk));
}

void CollisionSystem::handleProjectileEnemy(shared_ptr<Entity> projectile, shared_ptr<Entity> enemy, EntityManager &entityManager)
{
	shared_ptr<ProjectileComponent> projectile_info = projectile->getComponent<ProjectileComponent>();
	shared_ptr<SplineComponent> spline = projectile->getComponent<SplineComponent>();
	shared_ptr<DamageComponent> damage = enemy->getComponent<DamageComponent>();

	if (spline == nullptr) {
		// Not a boomerang projectile, remove it
		projectile->setComponent<DeathComponent>(make_shared<DeathComponent>());
	}

	if (damage == nullptr) {
		enemy->setComponent<DamageComponent>(make_shared<DamageComponent>(projectile_info->getAttackPower()));
	} else {
		damage->addDamageInstance(projectile_info->getAttackPower());
	}
}

void CollisionSystem::handleCollision(shared_ptr<Entity> e1, shared_ptr<Entity> e2, EntityManager &entityManager)
{
	bitset<ComponentType::max_count> isPlayer = entityManager.getComponentChecker(vector<int>{ComponentType::player});
	bitset<ComponentType::max_count> isResource = entityManager.getComponentChecker(vector<int>{ComponentType::resource});
	bitset<ComponentType::max_count> isEnemy = entityManager.getComponentChecker(vector<int>{ComponentType::enemy});
	bitset<ComponentType::max_count> isProjectile = entityManager.getComponentChecker(vector<int>{ComponentType::projectile});

	handleCollisionOfType(isPlayer, isResource, e1, e2, entityManager, handlePlayerResource);
	handleCollisionOfType(isProjectile, isEnemy, e1, e2, entityManager, handleProjectileEnemy);
  // handleCollisionOfType(isPlayer, isEnemy, e1, e2, entityManager, handlePlayerEnemy);
}
