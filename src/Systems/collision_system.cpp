#include "collision_system.hpp"

void CollisionSystem::setScreenInfo(vec2 _screen)
{
	screen = _screen;
}

EntityGrid CollisionSystem::preprocessEntitiesIntoGrid(vector<shared_ptr<Entity>> entities)
{
	EntityGrid grid(NUM_CELLS_IN_ROW, vector<vector<shared_ptr<Entity>>>(NUM_CELLS_IN_COLUMN, vector<shared_ptr<Entity>>{})); ;
	float cell_width = screen.x / NUM_CELLS_IN_ROW;
	float cell_height = screen.y / NUM_CELLS_IN_COLUMN;

	for (int x = 0; x < NUM_CELLS_IN_ROW; x++) {
		for (int y = 0; y < NUM_CELLS_IN_COLUMN; y++) {
			vec2 cell_pos = {x * cell_width, y * cell_height};
			vec2 cell_size = {cell_width, cell_height};

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

void CollisionSystem::checkCollisions(EntityManager &entityManager)
{
	vector<shared_ptr<Entity>> collidables = entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::collision}));
	EntityGrid grid = preprocessEntitiesIntoGrid(collidables);
	
	for (vector<vector<shared_ptr<Entity>>> row : grid) {
		for (vector<shared_ptr<Entity>> cell : row) {
			for (shared_ptr<Entity> e1 : cell) {
				for (shared_ptr<Entity> e2 : cell) {
					CollisionComponent *e1_collision = e1->getComponent<CollisionComponent>();
					CollisionComponent *e2_collision = e2->getComponent<CollisionComponent>();


					if (e1_collision->isCollidingWith(*e2_collision)) {
						handleCollision(e1, e2);						
					}	
				}
			}	
		}
	}	
}

void CollisionSystem::handleCollision(shared_ptr<Entity> e1, shared_ptr<Entity> e2)
{
	PlayerComponent *player = e1->getComponent<PlayerComponent>();	
	EnemyComponent *enemy = e2->getComponent<EnemyComponent>();

	if (player != nullptr && enemy != nullptr) {
			cout << "player and enemy collided" << endl;
	}
}
