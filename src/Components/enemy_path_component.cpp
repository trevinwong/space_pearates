#include "enemy_path_component.hpp"

EnemyPathComponent::EnemyPathComponent(int _type) {
  type = _type;
}

EnemyPathComponent::~EnemyPathComponent() {
>>>>>>> 62fb42eb5a726aa733ba567250a24250d809564c
}

void EnemyPathComponent::move (float dt, EntityManager& entityManager) {
  setMap(entityManager);
  if (type == turtle_shell) {
    moveShell(dt, entityManager);
  } else if (type == random) {
    EnemyPathComponent::moveRandom (dt, entityManager);
  } else {
    EnemyPathComponent::moveBasic(dt, entityManager);
  }
}

// Basic Movement: Tries to go vertically down to base until it can't, then goes in random
// horizontal direction till it can't
void EnemyPathComponent::moveBasic (float dt, EntityManager& entityManager) {
  srand(time(NULL));
  int arr[2] = {-1, 1};

  vector<shared_ptr<Entity>> entityList = entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::transform, ComponentType::enemy, ComponentType::movement}));
  shared_ptr<Entity> home = entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::home}))[0];

  float eps = 0.001;
  for (shared_ptr<Entity> e : entityList) {
    shared_ptr<MovementComponent> movementComponent = e->getComponent<MovementComponent>();
    shared_ptr<EnemyComponent> enemyComponent = e->getComponent<EnemyComponent>();
    shared_ptr<TransformComponent> transformComponent = e->getComponent<TransformComponent>();
    shared_ptr<HealthComponent> healthComponent = home->getComponent<HealthComponent>();

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
        healthComponent->curHP = healthComponent->curHP - enemyComponent->totalAtk  < 0 ? 0 : healthComponent->curHP - enemyComponent->totalAtk;
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
      shared_ptr<TransformComponent> tile_transform = tile->getComponent<TransformComponent>();
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
    shared_ptr<MovementComponent> movementComponent = e->getComponent<MovementComponent>();
    shared_ptr<EnemyComponent> enemyComponent = e->getComponent<EnemyComponent>();
    shared_ptr<TransformComponent> transformComponent = e->getComponent<TransformComponent>();
    shared_ptr<HealthComponent> healthComponent = home->getComponent<HealthComponent>();

    vec2 vel = movementComponent->velocity;
    vec2 pos = transformComponent->position;
    int yind = static_cast<int>(pos.y / 40);
    int xind = static_cast<int>(pos.x / 40);

    bool vflag = false;
    bool hflag = false;
    vel.y = abs(vel.y) < eps ? movementComponent->maxVelocity.y : vel.y;
    // vel.x = abs(vel.x) < eps ? movementComponent->maxVelocity.x : vel.x;

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

    for (int i = 0; i <= ceil(abs(vel.y)*dt/40); i++)
      if (map[yind+i][xind] == MAP_PLATFORM_TILE
         || map[yind+i][xind] == MAP_PLATFORM_TILE
         || map[yind+i][xind+1] == MAP_PLATFORM_TILE) {
        vflag = true;
        break;
      }

    if (vflag) {
      enemyComponent->ground = true;
      int dir = rand() % 2;
      vel.y = 0;
      vel.x = abs(vel.x) < eps ? arr[dir]*movementComponent->maxVelocity.x : vel.x;
    } else if (enemyComponent->ground) {
      vel.y = 0;
      vel.x = -vel.x;
    }
    if (pos.x + vel.x*dt >= (SCREEN_WIDTH - 50) || pos.x +vel.x*dt <= 20) {
      vel.x = -vel.x;
    }
    movementComponent->velocity = vel;
  }
}

void EnemyPathComponent::moveRandom (float dt, EntityManager& entityManager) {
  srand(time(NULL));
  int arr[2] = {-1, 1};

  vector<shared_ptr<Entity>> entityList = entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::transform, ComponentType::enemy, ComponentType::movement}));
  shared_ptr<Entity> home = entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::home}))[0];

  float eps = 0.001;
  for (shared_ptr<Entity> e : entityList) {
    shared_ptr<MovementComponent> movementComponent = e->getComponent<MovementComponent>();
    shared_ptr<EnemyComponent> enemyComponent = e->getComponent<EnemyComponent>();
    shared_ptr<TransformComponent> transformComponent = e->getComponent<TransformComponent>();
    shared_ptr<HealthComponent> healthComponent = home->getComponent<HealthComponent>();

    vec2 vel = movementComponent->velocity;
    vec2 pos = transformComponent->position;
    int yind = static_cast<int>(pos.y / 40);
    int xind = static_cast<int>(pos.x / 40);

    bool vflag = false;
    bool hflag = false;
    vel.y = abs(vel.y) < eps ? movementComponent->maxVelocity.y : vel.y;
    // vel.x = abs(vel.x) < eps ? movementComponent->maxVelocity.x : vel.x;

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

    for (int i = 0; i <= ceil(abs(vel.y)*dt/40); i++)
      if (map[yind+i][xind] == MAP_PLATFORM_TILE
         || map[yind+i][xind] == MAP_PLATFORM_TILE
         || map[yind+i][xind+1] == MAP_PLATFORM_TILE) {
        vflag = true;
        break;
      }

    if (vflag) {
      enemyComponent->ground = true;
      int dir = rand() % 2;
      vel.y = 0;
      vel.x = abs(vel.x) < eps ? arr[dir]*movementComponent->maxVelocity.x : vel.x;
    } else if (enemyComponent->ground) {
      vel.y = 0;
      vel.x = -vel.x;
    }
    if (pos.x + vel.x*dt >= (SCREEN_WIDTH - 50) || pos.x +vel.x*dt <= 20) {
      vel.x = -vel.x;
    }
    movementComponent->velocity = vel;
  }
}

void EnemyPathComponent::setMap (EntityManager& entityManager) {
  vector<shared_ptr<Entity>> entityList = entityManager.getEntities();
  tiles = entityManager.getEntities(entityManager.getComponentChecker(vector<int>{ComponentType::tile}));
  for (shared_ptr<Entity> e: entityList) {
    shared_ptr<MapComponent> mapComponent = e->getComponent<MapComponent>();
    if (!mapComponent) continue;
    map = mapComponent->mapData2DArray;
  }
}
