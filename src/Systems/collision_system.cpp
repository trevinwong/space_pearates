#include "collision_system.hpp"

void CollisionSystem::setScreenInfo(vec2 _screen)
{
  screen = _screen;
}

bool CollisionSystem::checkIfCellIndicesAreInBound(pair<int, int> cell, int num_cells_in_row, int num_cells_in_col)
{
    return (cell.first >= 0 && cell.first < num_cells_in_row && cell.second >= 0 && cell.second < num_cells_in_col);
}

EntityGrid CollisionSystem::preprocessEntitiesIntoGrid(vector<shared_ptr<Entity>> entities)
{
  int num_cells_in_row = screen.x / MIN_CELL_SIZE;
  int num_cells_in_col = screen.y / MIN_CELL_SIZE;
  float cell_width = screen.x / num_cells_in_row;
  float cell_height = screen.y / num_cells_in_col;
  EntityGrid grid(num_cells_in_row, vector<vector<shared_ptr<Entity>>>(num_cells_in_col, vector<shared_ptr<Entity>>{}));

  for (shared_ptr<Entity> e : entities) {
      shared_ptr<TransformComponent> transform = e->getComponent<TransformComponent>();
      vec2 top_left = transform->position;
      vec2 top_right = {transform->position.x + transform->size.x, transform->position.y};
      vec2 bottom_left = {transform->position.x, transform->position.y + transform->size.y};
      vec2 bottom_right = {transform->position.x + transform->position.x, transform->position.y + transform->size.y};

      pair<int, int> top_left_cell = make_pair((int) floor(top_left.x / MIN_CELL_SIZE), (int) floor(top_left.y / MIN_CELL_SIZE));
      pair<int, int> top_right_cell = make_pair((int) floor(top_right.x / MIN_CELL_SIZE), (int) floor(top_right.y / MIN_CELL_SIZE));
      pair<int, int> bottom_left_cell = make_pair((int) floor(bottom_left.x / MIN_CELL_SIZE), (int) floor(bottom_left.y / MIN_CELL_SIZE));
      pair<int, int> bottom_right_cell = make_pair((int) floor(bottom_right.x / MIN_CELL_SIZE), (int) floor(bottom_right.y / MIN_CELL_SIZE));

      if (checkIfCellIndicesAreInBound(top_left_cell, num_cells_in_row, num_cells_in_col)) {
          grid[top_left_cell.first][top_left_cell.second].push_back(e);
      }
      if (top_right_cell.first != top_left_cell.first) {
          if (checkIfCellIndicesAreInBound(top_right_cell, num_cells_in_row, num_cells_in_col)) {
              grid[top_right_cell.first][top_right_cell.second].push_back(e); // also in the cell next to it
          }
      }
      if (bottom_left_cell.second != top_left_cell.second) {
          if (checkIfCellIndicesAreInBound(bottom_left_cell, num_cells_in_row, num_cells_in_col)) {
              grid[bottom_left_cell.first][bottom_left_cell.second].push_back(e); // also in the cell below it
          }
      }
      if (bottom_right_cell.first != top_left_cell.first && bottom_right_cell.second != top_left_cell.second) {
          if (checkIfCellIndicesAreInBound(bottom_right_cell, num_cells_in_row, num_cells_in_col)) {
              grid[bottom_right_cell.first][bottom_right_cell.second].push_back(e);
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
  shared_ptr<PlayerComponent> playerComponent = player->getComponent<PlayerComponent>();
  shared_ptr<MovementComponent> playerMovement = player->getComponent<MovementComponent>();
  shared_ptr<TransformComponent> playerTransform = player->getComponent<TransformComponent>();
  shared_ptr<SpriteComponent> playerSprite = player->getComponent<SpriteComponent>();
  shared_ptr<TransformComponent> enemyTransform = enemy->getComponent<TransformComponent>();

	player->setComponent<DamageComponent>(make_shared<DamageComponent>(1.0f));
  playerComponent->movementState = PlayerMovementState::HITSTUN;
  playerComponent->movementStateDuration = Timer(0.5);
  playerComponent->healthState = PlayerHealthState::INVINCIBLE;
  playerComponent->healthStateDuration = Timer(3);
  Mix_PlayChannel(-1, AudioLoader::getInstance().player_hurt, 0);

  vec2 relativePosition = enemyTransform->position - playerTransform->position;
  vec2 knockback = vec2(300, -150);
  if (relativePosition.x > 0) knockback.x = -knockback.x;
  playerMovement->velocity = knockback;

  playerSprite->blinkTimer = Timer(0.2);

  player->removeComponent<CollisionComponent>();
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
  handleCollisionOfType(isPlayer, isEnemy, e1, e2, entityManager, handlePlayerEnemy);
}
