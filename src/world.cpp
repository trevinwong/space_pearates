#include "world.hpp"

World::World()
{
}

World::~World()
{
}

void World::init(glm::vec2 screen)
{
	vector<shared_ptr<Entity>> entities = entityManager.getEntities();
	projection = glm::ortho(0.0f, static_cast<GLfloat>(screen.x), static_cast<GLfloat>(screen.y), 0.0f, -1.0f, 1.0f);
	entityManager = EntityManager();

	enemy.loadEnemy(screen, entityManager);
	enemy.getMap(entityManager);
	Entity mapDataEntity = MapEntityFactory::createMapEntityFromFile(map_path("map0.txt"));
	entityManager.addEntity(mapDataEntity);
	tileMapSystem.loadTileMap(entityManager);

	PlayerFactory playerFactory;
	Entity p = playerFactory.build();
	entityManager.addEntity(p);
	physicsSystem.setScreenInfo(screen);
}

void World::update(float dt)
{
  enemy.getMap(entityManager);
  enemy.move(dt, entityManager);
  vector<shared_ptr<Entity>> entities = entityManager.getEntities();
	playerSystem.interpInput(entityManager, dt, keys, keysProcessed);
  physicsSystem.moveEntities(entityManager, dt);

  // Towers
  towerAttackSystem.checkRangeAndShootAimProjectiles(entityManager);
  towerAttackSystem.reduceElapsedTimeToNextFire(entityManager, dt);

  // OffScreen garbage check
  projectileGarbageSystem.destroyOffScreenEntities(entityManager);
}

void World::processInput(float dt)
{

}

void World::draw()
{
  spriteSystem.drawSprites(entityManager, projection);
  billboardSystem.drawBillboards(entityManager, projection);
  towerRangeDisplaySystem.drawRanges(entityManager, projection);
}

void World::destroy()
{

}
