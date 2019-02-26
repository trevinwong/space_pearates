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
        CollisionComponent *collision = e->getComponent<CollisionComponent>();
        if (Math::isCollidingWith(cell_pos, cell_size, collision->position, collision->size)) {
          grid[x][y].push_back(e);
        }
      }
    }
  }
  return grid;
}

void CollisionSystem::checkCollisions(EntityManager &entityManager, WavesetSystem &wavesetSystem)
{
  vector<shared_ptr<Entity>> collidables = entityManager.getEntities(
    entityManager.getComponentChecker(vector<int> {ComponentType::collision}));
  EntityGrid grid = preprocessEntitiesIntoGrid(collidables);

  for (vector<vector<shared_ptr<Entity>>> row : grid) {
    for (vector<shared_ptr<Entity>> cell : row) {
      for (shared_ptr<Entity> e1 : cell) {
        for (shared_ptr<Entity> e2 : cell) {
          CollisionComponent *e1_collision = e1->getComponent<CollisionComponent>();
          CollisionComponent *e2_collision = e2->getComponent<CollisionComponent>();

          if (e1_collision->isCollidingWith(*e2_collision)) {
            handleCollision(e1, e2, entityManager, wavesetSystem);
          }
        }
      }
    }
  }
}

void CollisionSystem::handleCollision(shared_ptr<Entity> e1, shared_ptr<Entity> e2, EntityManager &entityManager, WavesetSystem &wavesetSystem)
{

  srand(time(NULL));

  PlayerComponent *player = e1->getComponent<PlayerComponent>();
  ResourceComponent *resource = e2->getComponent<ResourceComponent>();
  if (player != nullptr && resource != nullptr) {
    // remove the resouce from world
    entityManager.removeEntity(e2);
    // Add the resource into wallet
    WalletComponent *wallet = e1->getComponent<WalletComponent>();
    if (wallet != nullptr) {
      // TODO: for diff type resources, increase diff amount
      wallet->earn(1);
      // update HUD resource counter
      // TODO: so far only coins, modify this part for diff types of resource
      HUD::getInstance().resource_count = wallet->coins;
    }
    Mix_PlayChannel(-1, AudioLoader::getInstance().collect_coin_sound, 0);
  }

  ProjectileComponent *projectile = e1->getComponent<ProjectileComponent>();
  EnemyComponent *enemy = e2->getComponent<EnemyComponent>();
  TransformComponent *pos = e2->getComponent<TransformComponent>();

  if (projectile != nullptr && enemy != nullptr) {
    entityManager.removeEntity(e2);
    entityManager.removeEntity(e1);
    if (pos && (rand() % 2 == 0)) {
      entityManager.addEntity(ResourceFactory::build(pos->position));
    }
		wavesetSystem.currentEnemies--;
  }
}
