#include "world.hpp"

// World class constructor is to set up data structures that will persist through multiple restarts.
World::World()
{
	eventSystem.subscribe<CollisionEvent>(&movementSystem);
	spriteSystem = SpriteSystem();
	tileMapSystem = TileMapSystem();
	enemy = Enemy();
	movementSystem = MovementSystem();
	playerSystem = PlayerSystem();
  collisionSystem = CollisionSystem();
  towerRangeDisplaySystem = TowerRangeDisplaySystem();
  towerAttackSystem = TowerAttackSystem();
}

World::~World()
{
}

// Data structures that should be re-initialized every restart of the world should be placed here.
void World::init(glm::vec2 screen)
{
	vector<shared_ptr<Entity>> entities = entityManager.getEntities();
	projection = glm::ortho(0.0f, static_cast<GLfloat>(screen.x), static_cast<GLfloat>(screen.y), 0.0f, -1.0f, 1.0f);
	entityManager = EntityManager();

	enemy.loadEnemy(screen, entityManager);
	Entity mapDataEntity = MapEntityFactory::createMapEntityFromFile(map_path("map0.txt"));
	entityManager.addEntity(mapDataEntity);
	tileMapSystem.loadTileMap(entityManager); // Add platform tiles

	// Generate the player entity
	PlayerFactory* playerFactory = new PlayerFactory();
	Entity p = playerFactory->build();
	entityManager.addEntity(p);
	movementSystem.setScreenInfo(screen);
}

// dt is known as delta time, how much time has passed since update was last called
void World::update(float dt)
{
	enemy.move();
	vector<shared_ptr<Entity>> entities = entityManager.getEntities();
	playerSystem.interpInput(entities, keys);
	collisionSystem.checkCollisions(eventSystem, entities);
	movementSystem.moveEntities(entities, dt);

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

// Possibly redundant - destructor can serve the same purpose.
// However, use this function anyways just in-case we need to explicitly call it.
void World::destroy()
{

}
