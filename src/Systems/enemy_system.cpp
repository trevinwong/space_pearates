#include "enemy_system.hpp"

// Just moves back & forth on a single platform & turtle shells people
// void EnemySystem::moveShell (float dt, EntityManager& entityManager) {
//   srand(time(NULL));
//   int arr[2] = {-1, 1};

//   vector<shared_ptr<Entity>> entityList = entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::transform, ComponentType::enemy, ComponentType::movement}));
//   shared_ptr<Entity> home = entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::home}))[0];

//   float eps = 0.001;
//   for (shared_ptr<Entity> e : entityList) {
//     MovementComponent *movementComponent = e->getComponent<MovementComponent>();
//     EnemyComponent *enemyComponent = e->getComponent<EnemyComponent>();
//     TransformComponent *transformComponent = e->getComponent<TransformComponent>();
//     HealthComponent *healthComponent = home->getComponent<HealthComponent>();

// 		vec2 vel = movementComponent->velocity;
// 		vec2 pos = transformComponent->position;
// 		int yind = static_cast<int>(pos.y / 40);
// 		int xind = static_cast<int>(pos.x / 40);
// 		bool flag = false;
// 		vel.y = abs(vel.y) < eps ? movementComponent->maxVelocity.y : vel.y;

//     if (map[yind][xind] == MAP_BASE_POSITION) {
//       entityManager.removeEntity(e);
// 			WavesetSystem::getInstance().decrementEnemies(1, entityManager);
//       if (healthComponent) {
//         healthComponent->curHP = healthComponent->curHP - 20 < 0 ? 0 : healthComponent->curHP - 20;
//          if (healthComponent->curHP <= 0) {
//             HUD::getInstance().game_over = true;
//          }
//       }
//     }

// 		for (int i = 0; i <= ceil(vel.y*dt/40); i++)
// 			if (map[yind+i][xind] == MAP_PLATFORM_TILE || map[yind+i][xind+1] == MAP_PLATFORM_TILE)
// 				flag = true;

// 		if (flag) {
// 			int dir = rand() % 2;
// 			vel.x = abs(vel.x) < eps ? arr[dir]*movementComponent->maxVelocity.x : vel.x;
// 			if (vel.x > 0)
// 				vel.x = pos.x + vel.x*dt < 1200.0 ? vel.x : -vel.x;
// 			else vel.x = pos.x + vel.x*dt > 60 ? vel.x : -vel.x;
// 			vel.y = 0;
// 		} else vel.x = 0;

//     for (shared_ptr<Entity> tile : tiles) {
//       TransformComponent* tile_transform = tile->getComponent<TransformComponent>();
//       if (transformComponent->isCollidingWith(*tile_transform)) {
//         vel.x = -vel.x;
//       }
//     }

// 		// check if directly above base - path straight down if so
// 		for (int i = 0; i <= ceil(vel.y*dt/40); i++)
// 			if (map[yind+i][xind] == MAP_BASE_POSITION || map[yind-1][xind] == MAP_BASE_POSITION) {
// 				vel.y = movementComponent->maxVelocity.y;
// 				movementComponent->maxVelocity.x = 0.f;
// 			}


// 		movementComponent->velocity = vel;
//   }
// }

void EnemySystem::move (float dt, EntityManager& entityManager) {
  vector<shared_ptr<Entity>> entityList = entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::transform, ComponentType::enemy, ComponentType::movement}));
  for (shared_ptr<Entity> e : entityList) {
    EnemyPathComponent *pathfind = e->getComponent<EnemyPathComponent>();
    if (pathfind) {
      pathfind->move(dt, entityManager);
    }
  }
}

// Super simple AI; just tries to go down the map until it hits base
// If it can't go down anymore, randomly goes right / left till it can go down
// void EnemySystem::move (float dt, EntityManager& entityManager) {
//   srand(time(NULL));
//   int arr[2] = {-1, 1};

//   vector<shared_ptr<Entity>> entityList = entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::transform, ComponentType::enemy, ComponentType::movement}));
//   shared_ptr<Entity> home = entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::home}))[0];

//   float eps = 0.001;
//   for (shared_ptr<Entity> e : entityList) {
//     MovementComponent *movementComponent = e->getComponent<MovementComponent>();
//     EnemyComponent *enemyComponent = e->getComponent<EnemyComponent>();
//     TransformComponent *transformComponent = e->getComponent<TransformComponent>();
//     HealthComponent *healthComponent = home->getComponent<HealthComponent>();

//     vec2 vel = movementComponent->velocity;
//     vec2 pos = transformComponent->position;
//     int yind = static_cast<int>(pos.y / 40);
//     int xind = static_cast<int>(pos.x / 40);

//     bool flag = false;
//     vel.y = abs(vel.y) < eps ? movementComponent->maxVelocity.y : vel.y;

//     if (map[yind][xind] == MAP_BASE_POSITION) {
//       entityManager.removeEntity(e);
//       WavesetSystem::getInstance().decrementEnemies(1, entityManager);
//       if (healthComponent) {
//         healthComponent->curHP = healthComponent->curHP - 20 < 0 ? 0 : healthComponent->curHP - 20;
//          if (healthComponent->curHP <= 0) {
//             HUD::getInstance().game_over = true;
//          }
//       }
//     }

//     for (int i = 0; i <= ceil(vel.y*dt/40); i++)
//       if (map[yind+i][xind] == MAP_PLATFORM_TILE || map[yind+i][xind+1] == MAP_PLATFORM_TILE)
//         flag = true;

//     if (flag) {
//       int dir = rand() % 2;
//       vel.x = abs(vel.x) < eps ? arr[dir]*movementComponent->maxVelocity.x : vel.x;
//       if (vel.x > 0)
//         vel.x = pos.x + vel.x*dt < 1200.0 ? vel.x : -vel.x;
//       else vel.x = pos.x + vel.x*dt > 60 ? vel.x : -vel.x;
//       vel.y = 0;
//     } else vel.x = 0;

//     // check if directly above base - path straight down if so
//     for (int i = 0; i <= ceil(vel.y*dt/40); i++)
//       if (map[yind+i][xind] == MAP_BASE_POSITION) {
//         vel.y = movementComponent->maxVelocity.y;
//         movementComponent->maxVelocity.x = 0.f;
//       }
//     movementComponent->velocity = vel;
//   }
// }

// void EnemySystem::moveRandom (float dt, EntityManager& entityManager) {
//   srand(time(NULL));
//   int arr[2] = {-1, 1};

//   vector<shared_ptr<Entity>> entityList = entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::transform, ComponentType::enemy, ComponentType::movement}));
//   shared_ptr<Entity> home = entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::home}))[0];

//   float eps = 0.001;
//   for (shared_ptr<Entity> e : entityList) {
//     MovementComponent *movementComponent = e->getComponent<MovementComponent>();
//     EnemyComponent *enemyComponent = e->getComponent<EnemyComponent>();
//     TransformComponent *transformComponent = e->getComponent<TransformComponent>();
//     HealthComponent *healthComponent = home->getComponent<HealthComponent>();

//     vec2 vel = movementComponent->velocity;
//     vec2 pos = transformComponent->position;
//     int yind = static_cast<int>(pos.y / 40);
//     int xind = static_cast<int>(pos.x / 40);

//     bool flag = false;
//     vel.y = abs(vel.y) < eps ? movementComponent->maxVelocity.y : vel.y;

//     if (map[yind][xind] == MAP_BASE_POSITION) {
//       entityManager.removeEntity(e);
//       WavesetSystem::getInstance().decrementEnemies(1, entityManager);
//       if (healthComponent) {
//         healthComponent->curHP = healthComponent->curHP - 20 < 0 ? 0 : healthComponent->curHP - 20;
//          if (healthComponent->curHP <= 0) {
//             HUD::getInstance().game_over = true;
//          }
//       }
//     }

//     for (int i = 0; i <= ceil(vel.y*dt/40); i++)
//       if (map[yind+i][xind] == MAP_PLATFORM_TILE || map[yind+i][xind+1] == MAP_PLATFORM_TILE)
//         flag = true;

//     int dir = rand() % 2;
//     vel.x = abs(vel.x) < eps ? arr[dir]*movementComponent->maxVelocity.x : vel.x;
//     if (vel.x > 0)
//       vel.x = pos.x + vel.x*dt < 1200.0 ? vel.x : -vel.x;
//     else vel.x = pos.x + vel.x*dt > 60 ? vel.x : -vel.x;

//     // check if directly above base - path straight down if so
//     for (int i = 0; i <= ceil(vel.y*dt/40); i++)
//       if (map[yind+i][xind] == MAP_BASE_POSITION) {
//         vel.y = movementComponent->maxVelocity.y;
//         movementComponent->maxVelocity.x = 0.f;
//       }
//     movementComponent->velocity = vel;
//   }
// }

void EnemySystem::setMap (EntityManager& entityManager) {
  shared_ptr<Entity> e = entityManager.getEntitiesHasOneOf(entityManager.getComponentChecker(vector<int>{ComponentType::map}))[0];
  MapComponent *mapComponent = e->getComponent<MapComponent>();
  tiles = entityManager.getEntities(entityManager.getComponentChecker(vector<int>{ComponentType::tile}));
 // if (!mapComponent) return false;
  map = mapComponent->mapData2DArray;
  // return true;
}