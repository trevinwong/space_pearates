#include "enemy_path_component.hpp"

EnemyPathComponent::EnemyPathComponent(int _type) {
  type = _type;
}

void EnemyPathComponent::move (float dt, EntityManager& entityManager) {
  setMap(entityManager);
  if (type == turtle_shell) {
    printf("turtle shell\n");
    moveShell(dt, entityManager);
  } else if (type == random) {
    // EnemyPathComponent::moveRandom (dt, entityManager);
  } else {
    printf("default\n");
    EnemyPathComponent::moveBasic(dt, entityManager);
  }
}

// Just moves back & forth on a single platform & turtle shells people
void EnemyPathComponent::moveBasic (float dt, EntityManager& entityManager) {
  srand(time(NULL));
  int arr[2] = {-1, 1};

  vector<shared_ptr<Entity>> entityList = entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::transform, ComponentType::enemy, ComponentType::movement}));
  shared_ptr<Entity> home = entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::home}))[0];

  float eps = 0.001;
  for (shared_ptr<Entity> e : entityList) {
    MovementComponent *movementComponent = e->getComponent<MovementComponent>();
    EnemyComponent *enemyComponent = e->getComponent<EnemyComponent>();
    TransformComponent *transformComponent = e->getComponent<TransformComponent>();
    HealthComponent *healthComponent = home->getComponent<HealthComponent>();

    vec2 vel = movementComponent->velocity;
    vec2 pos = transformComponent->position;
    int yind = static_cast<int>(pos.y / 40);
    int xind = static_cast<int>(pos.x / 40);
    bool flag = false;
    vel.y = abs(vel.y) < eps ? movementComponent->maxVelocity.y : vel.y;

    printf("%c\n", map[0][0]);
    if (map[yind][xind] == MAP_BASE_POSITION) {
      entityManager.removeEntity(e);
      WavesetSystem::getInstance().decrementEnemies(1, entityManager);
      if (healthComponent) {
        healthComponent->curHP = healthComponent->curHP - 20 < 0 ? 0 : healthComponent->curHP - 20;
         if (healthComponent->curHP <= 0) {
            HUD::getInstance().game_over = true;
         }
      }
    }

    for (int i = 0; i <= ceil(vel.y*dt/40); i++)
      if (map[yind+i][xind] == MAP_PLATFORM_TILE || map[yind+i][xind+1] == MAP_PLATFORM_TILE)
        flag = true;

    if (flag) {
      int dir = rand() % 2;
      vel.x = abs(vel.x) < eps ? arr[dir]*movementComponent->maxVelocity.x : vel.x;
      if (vel.x > 0)
        vel.x = pos.x + vel.x*dt < 1200.0 ? vel.x : -vel.x;
      else vel.x = pos.x + vel.x*dt > 60 ? vel.x : -vel.x;
      vel.y = 0;
    } else vel.x = 0;

    for (shared_ptr<Entity> tile : tiles) {
      TransformComponent* tile_transform = tile->getComponent<TransformComponent>();
      if (transformComponent->isCollidingWith(*tile_transform)) {
        vel.x = -vel.x;
      }
    }

    // check if directly above base - path straight down if so
    for (int i = 0; i <= ceil(vel.y*dt/40); i++)
      if (map[yind+i][xind] == MAP_BASE_POSITION) {
        vel.y = movementComponent->maxVelocity.y;
        movementComponent->maxVelocity.x = 0.f;
      }
    movementComponent->velocity = vel;
  }
}

void EnemyPathComponent::moveShell (float dt, EntityManager& entityManager) {
  srand(time(NULL));
  int arr[2] = {-1, 1};

  vector<shared_ptr<Entity>> entityList = entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::transform, ComponentType::enemy, ComponentType::movement}));
  shared_ptr<Entity> home = entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::home}))[0];

  float eps = 0.001;
  for (shared_ptr<Entity> e : entityList) {
    MovementComponent *movementComponent = e->getComponent<MovementComponent>();
    EnemyComponent *enemyComponent = e->getComponent<EnemyComponent>();
    TransformComponent *transformComponent = e->getComponent<TransformComponent>();
    HealthComponent *healthComponent = home->getComponent<HealthComponent>();

    vec2 vel = movementComponent->velocity;
    vec2 pos = transformComponent->position;
    int yind = static_cast<int>(pos.y / 40);
    int xind = static_cast<int>(pos.x / 40);

    bool flag = false;
    vel.y = abs(vel.y) < eps ? movementComponent->maxVelocity.y : vel.y;

    if (map[yind][xind] == MAP_BASE_POSITION) {
      entityManager.removeEntity(e);
      WavesetSystem::getInstance().decrementEnemies(1, entityManager);
      if (healthComponent) {
        healthComponent->curHP = healthComponent->curHP - 20 < 0 ? 0 : healthComponent->curHP - 20;
         if (healthComponent->curHP <= 0) {
            HUD::getInstance().game_over = true;
         }
      }
    }

    for (int i = 0; i <= ceil(vel.y*dt/40); i++)
      if (map[yind+i][xind] == MAP_PLATFORM_TILE || map[yind+i][xind+1] == MAP_PLATFORM_TILE)
        flag = true;

    if (flag) {
      int dir = rand() % 2;
      vel.x = abs(vel.x) < eps ? arr[dir]*movementComponent->maxVelocity.x : vel.x;
      if (vel.x > 0)
        vel.x = pos.x + vel.x*dt < 1200.0 ? vel.x : -vel.x;
      else vel.x = pos.x + vel.x*dt > 60 ? vel.x : -vel.x;
      vel.y = 0;
    } else vel.x = 0;

    // check if directly above base - path straight down if so
    for (int i = 0; i <= ceil(vel.y*dt/40); i++)
      if (map[yind+i][xind] == MAP_BASE_POSITION) {
        vel.y = movementComponent->maxVelocity.y;
        movementComponent->maxVelocity.x = 0.f;
      }
    movementComponent->velocity = vel;
  }
}

void EnemyPathComponent::setMap (EntityManager& entityManager) {
  vector<shared_ptr<Entity>> entityList = entityManager.getEntities();
  vector<shared_ptr<Entity>> tiles = entityManager.getEntities(entityManager.getComponentChecker(vector<int>{ComponentType::tile}));
  for (shared_ptr<Entity> e: entityList) {
    MapComponent *mapComponent = e->getComponent<MapComponent>();
    if (!mapComponent) continue;
    map = mapComponent->mapData2DArray;
    printf("set map\n");
  }
}
