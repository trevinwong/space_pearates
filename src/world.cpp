#include "world.hpp"

World::World()
{
}

World::~World()
{
}

void World::init(vec2 screen)
{
	collisionSystem.setScreenInfo(screen);
  vector<shared_ptr<Entity>> entities = entityManager.getEntities();
	projection = glm::ortho(0.0f, static_cast<GLfloat>(screen.x), static_cast<GLfloat>(screen.y), 0.0f, -1.0f, 1.0f);
	entityManager = EntityManager();

	Entity r = ResourceFactory::build(vec2(screen.x / 2, 50));
	entityManager.addEntity(r);
  ResourceFactory::spawnMany(entityManager);

  vec2 playerSpawnPt = vec2(screen.x / 8, screen.y / 8);
  printVec2("playerSpawnPt", playerSpawnPt);
	Entity p = PlayerFactory::build(playerSpawnPt, vec2(50.0f, 65.0f));
	entityManager.addEntity(p);

	Entity mapDataEntity = MapEntityFactory::createMapEntityFromFile(map_path("map0.txt"));
	entityManager.addEntity(mapDataEntity);
	tileMapSystem.loadTileMap(entityManager);

  entityManager.addEntity(EnemySpawnFactory::build(2.0));

	enemySystem.getMap(entityManager);
	physicsSystem.setScreenInfo(screen);

  // Generate the build tower ui entity
  vector<Entity> towerUiEntities = TowerUiEntityFactory::createTowerUiButtons();
  for(Entity towerUiEntity : towerUiEntities)
    entityManager.addEntity(towerUiEntity);
}

void World::update(float dt)
{
  enemySpawnSystem.spawnEnemy(entityManager);
  enemySpawnSystem.reduceElapsedTime(entityManager, dt);

	enemySystem.move(dt, entityManager);

  vector<shared_ptr<Entity>> entities = entityManager.getEntities();
  playerSystem.interpInput(entityManager, dt, keys, keysProcessed);
  physicsSystem.moveEntities(entityManager, dt);
	collisionSystem.checkCollisions(entityManager);
	spriteSystem.updateElapsedTime(dt);
  
  // Build Tower UI
  towerUiSystem.interpInput(entityManager, keys);
  towerUiSystem.update(entityManager, dt);

  // Towers
  towerAttackSystem.checkRangeAndShootProjectiles(entityManager);
  towerAttackSystem.reduceElapsedTimeToNextFire(entityManager, dt);

  // OffScreen garbage check
  projectileGarbageSystem.destroyOffScreenEntities(entityManager);
	resourceSystem.handleResourceSpawnAndDespawn(entityManager, dt);

	/*
	for (shared_ptr<Entity> e: entities) {
		CollisionComponent *collision = e->getComponent<CollisionComponent>();
		TransformComponent *transform = e->getComponent<TransformComponent>();
		if (collision != nullptr and transform != nullptr) {
			printVec2("transform", transform->position);
			printVec2("collision", collision->position);
		}
	}
	*/
}

void World::processInput(float dt)
{

}

void World::draw()
{
  spriteSystem.drawSprites(entityManager, projection);
  billboardSystem.drawBillboards(entityManager, projection);
  towerRangeDisplaySystem.drawRanges(entityManager, projection);
  towerUiSystem.render(entityManager, projection);
  HUD::getInstance().draw();
}

void World::destroy()
{

}
