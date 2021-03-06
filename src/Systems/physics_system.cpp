#include "physics_system.hpp"

void PhysicsSystem::setScreenInfo(vec2 info)
{
  screenInfo = info;
}

float PhysicsSystem::getGravity(float dt)
{
	return GRAVITY * dt;
}

float PhysicsSystem::getFriction(vec2 velocity, float dt)
{
	int direction = (velocity.x > 0) - (velocity.x < 0);
	return -direction * FRICTION * dt;
}

void PhysicsSystem::moveEntities(EntityManager &entityManager, float dt) {
	vector<shared_ptr<Entity>> entities = entityManager.getEntities(entityManager.getComponentChecker(
    vector<int>{ComponentType::transform, ComponentType::movement}));

  for (shared_ptr<Entity> e : entities) {
		shared_ptr<TransformComponent> transform = e->getComponent<TransformComponent>();
		shared_ptr<MovementComponent> movement = e->getComponent<MovementComponent>();
		shared_ptr<EnemyPathComponent> pathfind = e->getComponent<EnemyPathComponent>();
		auto pathtype = pathfind ? pathfind->type : NULL;
		if (pathtype != 2 && pathtype != 3) movement->accel.y += getGravity(dt);
		movement->accel.x += getFriction(movement->velocity, dt);
		movement->accel = glm::clamp(movement->accel, -movement->maxAccel, movement->maxAccel);

		vec2 newVelocity = {movement->velocity.x + movement->accel.x * dt, movement->velocity.y + movement->accel.y * dt};
		if (glm::dot(movement->velocity.x, newVelocity.x) < 0) {
			movement->accel.x = 0;
			newVelocity.x = 0;
		}


    // Clamping velocity based on magnitude now. Uses y max velocity but change later
    if (glm::length(newVelocity) != 0) {
      float newVelocityMagnitude = glm::clamp(glm::length(newVelocity), -movement->maxVelocity.y, movement->maxVelocity.y);
      vec2 newVelocityDirection = glm::normalize(newVelocity);
      newVelocity = newVelocityDirection * newVelocityMagnitude;
    }

		movement->velocity = newVelocity;

		shared_ptr<CollisionComponent> collision = e->getComponent<CollisionComponent>();
		shared_ptr<ProjectileComponent> projectile = e->getComponent<ProjectileComponent>();
		shared_ptr<WaterTowerFactorComponent> waterTowerFactor = e->getComponent<WaterTowerFactorComponent>();

    if (waterTowerFactor) {
      transform->position = transform->position + movement->velocity * waterTowerFactor->speedFactor * dt;
		}
		else {
      transform->position = transform->position + movement->velocity * dt;
		}
		if (projectile == nullptr && pathtype !=2 && pathtype != 3) adjustPositionAroundTiles(entityManager, e);
		if (collision != nullptr) collision->position = transform->position;
		if (!movement->offScreenOK) adjustPositionOntoScreen(entityManager, e);
	}
}

void PhysicsSystem::rotateEntities(EntityManager & entityManager, float dt)
{
  vector<shared_ptr<Entity>> entities = entityManager.getEntities(entityManager.getComponentChecker(
    vector<int>{ComponentType::transform, ComponentType::projectile}));
  for (shared_ptr<Entity> e : entities) {
		shared_ptr<TransformComponent> transform = e->getComponent<TransformComponent>();
		shared_ptr<ProjectileComponent> projectile = e->getComponent<ProjectileComponent>();

    if (projectile->rotateOn) transform->rotation += 10.0 * dt;

		shared_ptr<CollisionComponent> collision = e->getComponent<CollisionComponent>();
    if (collision != nullptr) collision->rotation = transform->rotation;
  }
}

void PhysicsSystem::adjustPositionAroundTiles(EntityManager &entityManager, shared_ptr<Entity> &e) {
	vector<shared_ptr<Entity>> tiles = entityManager.getEntities(entityManager.getComponentChecker(vector<int>{ComponentType::tile}));
	shared_ptr<TransformComponent> transform = e->getComponent<TransformComponent>();
	shared_ptr<MovementComponent> movement = e->getComponent<MovementComponent>();

	for (shared_ptr<Entity> tile : tiles) {
		shared_ptr<TileComponent> tile_info = tile->getComponent<TileComponent>();
    if (!tile_info->isPhysical) continue;

		shared_ptr<TransformComponent> tile_transform = tile->getComponent<TransformComponent>();

		if (transform->isCollidingWith(*tile_transform)) {
			float radius = transform->size.x / 2.0f; // convert collision box into a circular one

			vec2 center = transform->position + (transform->size / 2.0f);
			vec2 tile_center = tile_transform->position + (tile_transform->size / 2.0f);

			vec2 top_left_pt = {tile_transform->position.x, tile_transform->position.y};
			vec2 top_right_pt = {tile_transform->position.x + tile_transform->size.x, tile_transform->position.y};
			vec2 bottom_left_pt = {tile_transform->position.x, tile_transform->position.y + tile_transform->size.y};
			vec2 bottom_right_pt = {tile_transform->position.x + tile_transform->size.x, tile_transform->position.y + tile_transform->size.y};

			Line top_edge(top_left_pt, top_right_pt);
			Line bottom_edge(bottom_left_pt, bottom_right_pt);
			Line left_edge(top_left_pt, bottom_left_pt);
			Line right_edge(top_right_pt, bottom_right_pt);

			Line player_to_tile(center, tile_center);

			vec2 top_intersect = player_to_tile.getLineSegsIntersection(top_edge);
			vec2 bottom_intersect = player_to_tile.getLineSegsIntersection(bottom_edge);
			vec2 left_intersect = player_to_tile.getLineSegsIntersection(left_edge);
			vec2 right_intersect = player_to_tile.getLineSegsIntersection(right_edge);

			float epsilon = radius / 2.5;
			bool top_intersect_valid = (distance(center, top_intersect) <= radius + epsilon);
			bool bottom_intersect_valid = (distance(center, bottom_intersect) <= radius + epsilon);
			bool left_intersect_valid = (distance(center, left_intersect) <= radius + epsilon);
			bool right_intersect_valid = (distance(center, right_intersect) <= radius + epsilon);

			vec2 newVelocity = movement->velocity;
			vec2 newAccel = movement->accel;

			shared_ptr<PlayerComponent> player = e->getComponent<PlayerComponent>();

			if (player != nullptr && top_intersect_valid) {
				player->jumps = player->maxJumps;
			}

			if (top_intersect_valid || bottom_intersect_valid) {
				newVelocity.y = 0.0f;
				newAccel.y = 0.0f;
			}

			if (left_intersect_valid || right_intersect_valid) {
				newVelocity.x = 0.0f;
				newAccel.x = 0.0f;
			}

			movement->velocity = newVelocity;
			movement->accel = newAccel;

			vec2 newPosition = transform->position;

			if (top_intersect_valid) newPosition.y = top_left_pt.y - transform->size.y;
			if (bottom_intersect_valid) newPosition.y = bottom_left_pt.y;
			if (left_intersect_valid) newPosition.x = top_left_pt.x - transform->size.x;
			if (right_intersect_valid) newPosition.x = top_right_pt.x;

			transform->position = newPosition;
		}
	}
}

void PhysicsSystem::adjustPositionOntoScreen(EntityManager &entityManager, shared_ptr<Entity> &e)
{
	shared_ptr<TransformComponent> transform = e->getComponent<TransformComponent>();
	shared_ptr<MovementComponent> movement = e->getComponent<MovementComponent>();
	if (transform->position.x < 0.0f) {
		transform->position.x = 0.0f;
		movement->velocity.x = 0.0f;
		movement->accel.x = 0.0f;
	}
	if (transform->position.x + transform->size.x > screenInfo.x) {
		transform->position.x = screenInfo.x - transform->size.x;
		movement->velocity.x = 0.0f;
		movement->accel.x = 0.0f;
	}
}
