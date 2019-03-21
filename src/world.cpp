#include "world.hpp"

// Entities that we do not want to erase upon resetting, can be reused
const vector<int> non_recyclable_components = {
  ComponentType::tile, ComponentType::map, ComponentType::home, ComponentType::background_sprite, ComponentType::player, ComponentType::particle,
  ComponentType::waveset }; // TODO: eventually move WavesetManagerFactory(WavesetComponent) functionality to WavesetSystem singleton...

World::World(std::weak_ptr<SceneManager> _sceneManager) : AbstractScene(_sceneManager)
{
  vec2 screen =  vec2(SCREEN_WIDTH, SCREEN_HEIGHT);
  projection = glm::ortho(0.0f, static_cast<GLfloat>(screen.x), static_cast<GLfloat>(screen.y), 0.0f, -1.0f, 1.0f);
  physicsSystem.setScreenInfo(screen);
  collisionSystem.setScreenInfo(screen);
  entityManager = EntityManager();

  entityManager.addEntity(MapEntityFactory::createMapEntityFromFile(map_path("map0.txt")));
  TileMapSystem::loadTileMap(entityManager, player_spawn);
  WavesetSystem::getInstance().enemySpawnPoints = TileMapSystem::enemySpawnPoints;
  entityManager.addEntity(PlayerFactory::build(player_spawn));
  // Spawn starting resources
  ResourceFactory::spawnInitial(entityManager);

  enemySystem.setMap(entityManager);
  entityManager.addEntity(WavesetManagerFactory::build(waveset_path("waveset0.txt")));

  entityManager.addEntity(BackgroundEntityFactory::createBackgroundEntity("earth_bg.png", false, vec2(2304, 1620)));
  entityManager.addEntity(TowerUiEntityFactory::create());

  particleSystem.initParticleSystem(entityManager); // adds particle entities pool
  renderToTextureSystem.initWaterEffect();
}

void World::reset()
{
  // Reset singletons
  HUD::getInstance().reset();
  AudioLoader::getInstance().reset();
  WavesetSystem::getInstance().reset();

  // Remove all recyclable entities
  entityManager.filterRemoveByComponentType(non_recyclable_components);

  // Reset map tower data
  shared_ptr<Entity> map = entityManager.getEntitiesHasOneOf(entityManager.getComponentChecker(ComponentType::map))[0];
  map->getComponent<MapComponent>()->reset();
  // Reset particles pool
  particleSystem.resetParticles(entityManager);
  // Reset home health to max
  shared_ptr<Entity> home = entityManager.getEntitiesHasOneOf(entityManager.getComponentChecker(ComponentType::home))[0];
  home->getComponent<HealthComponent>()->reset();
  // Reset player position and wallet
  shared_ptr<Entity> player = entityManager.getEntitiesHasOneOf(entityManager.getComponentChecker(vector<int>{ComponentType::player, ComponentType::wallet}))[0];
  player->getComponent<TransformComponent>()->position = player_spawn;
  player->getComponent<WalletComponent>()->coins = 0;

  // Spawn starting resources
  ResourceFactory::spawnInitial(entityManager);            // adds 6 entities
  entityManager.addEntity(TowerUiEntityFactory::create()); // adds 1 entity

  paused = false;
  HelpMenu::getInstance().showHelp = false;
}

void World::processInput(float dt, GLboolean keys[], GLboolean keysProcessed[])
{
  if (keys[GLFW_KEY_R] && !keysProcessed[GLFW_KEY_R])
  {
    reset();
    keysProcessed[GLFW_KEY_R] = true;
    return;
  }
  if (keys[GLFW_KEY_M] && !keysProcessed[GLFW_KEY_M])
  {
    AudioLoader::getInstance().changeBgm();
    keysProcessed[GLFW_KEY_M] = true;
  }
  if (keys[GLFW_KEY_H] && !keysProcessed[GLFW_KEY_H])
  {
    paused = !paused;
    HelpMenu::getInstance().showHelp = paused;
    keysProcessed[GLFW_KEY_H] = true;
  }
  if (keys[GLFW_KEY_P] && !keysProcessed[GLFW_KEY_P])
  {
    paused = !paused;
    HelpMenu::getInstance().showHelp = paused;
    keysProcessed[GLFW_KEY_P] = true;
  }
  if (keys[GLFW_KEY_ESCAPE] && !keysProcessed[GLFW_KEY_ESCAPE])
  {
    if(shared_ptr<SceneManager> sceneManager_ptr = sceneManager.lock()){
      sceneManager_ptr->setNextSceneToMainMenu();
    }
    paused = false;
    HelpMenu::getInstance().showHelp = false;
    keysProcessed[GLFW_KEY_ESCAPE] = true;
  }
  if (paused) return;

  playerSystem.interpInput(entityManager, dt, keys, keysProcessed);
  towerUiSystem.interpInput(entityManager, keys, keysProcessed);
}

void World::update(float dt)
{
  if (paused) return;

  // Note: Be careful, order may matter in some cases for systems
  HUD::getInstance().update(dt);

  WavesetSystem::getInstance().handleBuildAndDefensePhase(entityManager, dt);
  enemySystem.move(dt, entityManager);
  physicsSystem.moveEntities(entityManager, dt);
  physicsSystem.rotateEntities(entityManager, dt);
  interpolationSystem.update(entityManager, dt);
  collisionSystem.checkCollisions(entityManager);
  spriteSystem.updateElapsedTime(dt);

  // Background Update
  backgroundSystem.update(entityManager);

  // Build Tower UI
  towerUiSystem.update(entityManager, dt);

  // Towers
  towerAttackSystem.checkRangeAndShootProjectiles(entityManager);
  towerAttackSystem.reduceElapsedTimeToNextFire(entityManager, dt);

  // Remove entities
  offscreenGarbageSystem.destroyEntitiesContainingAll(entityManager, vector<int>{ComponentType::projectile, ComponentType::movement});
  offscreenGarbageSystem.destroyEntitiesContainingAll(entityManager, vector<int>{ComponentType::resource});
  resourceSystem.handleResourceSpawnAndDespawn(entityManager, dt);
  particleSystem.updateParticles(entityManager, dt);
  damageSystem.handleDamage(entityManager);
  deathSystem.handleDeaths(entityManager);
}

void World::draw()
{
  // get ready to render to texture
  renderToTextureSystem.beforeRenderWaterEffect();
  // Background will render first
  backgroundSystem.render(entityManager, projection);
  spriteSystem.drawSprites(entityManager, projection);
  // so far everything rendered into buffer
  // add effects to the buffer and render this buffer to screen
  renderToTextureSystem.drawWaterEffect(entityManager, projection);

  billboardSystem.drawBillboards(entityManager, projection);
  towerRangeDisplaySystem.drawRanges(entityManager, projection);
  towerUiSystem.render(entityManager, projection);
  HUD::getInstance().draw();


  HelpMenu::getInstance().draw(projection);
}
