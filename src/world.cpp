#include "world.hpp"

// Entities that we do not want to erase upon resetting, can be reused
const vector<int> non_recyclable_components = {
  ComponentType::tile, ComponentType::map, ComponentType::home, ComponentType::background_sprite, ComponentType::particle,
  ComponentType::waveset }; // TODO: eventually move WavesetManagerFactory(WavesetComponent) functionality to WavesetSystem singleton...

World::World(std::weak_ptr<SceneManager> _sceneManager, int _level) : AbstractScene(_sceneManager), level(_level)
{
  AudioLoader::getInstance().playGameMusic();
  vec2 screen =  vec2(SCREEN_WIDTH, SCREEN_HEIGHT);
  TowerDataLoader::loadTowerData();
  PlayerDataLoader::loadPlayerData();
  projection = glm::ortho(0.0f, static_cast<GLfloat>(screen.x), static_cast<GLfloat>(screen.y), 0.0f, -1.0f, 1.0f);
  physicsSystem.setScreenInfo(screen);
  collisionSystem.setScreenInfo(screen);
  entityManager = EntityManager();

  string mapName = "map" + std::to_string(level) + ".txt";
  map = make_shared<Entity>(MapEntityFactory::createMapEntityFromFile(map_path()+mapName));
  entityManager.addEntity(map);
  TileMapSystem::loadTileMap(entityManager);
  home = entityManager.getEntitiesHasOneOf(entityManager.getComponentChecker(ComponentType::home))[0];
  WavesetSystem::getInstance().enemySpawnPoints = TileMapSystem::enemySpawnPoints;
  player = make_shared<Entity>(PlayerFactory::build(TileMapSystem::player_spawn));
  entityManager.addEntity(player);

  // Spawn starting resources
  ResourceFactory::spawnInitial(entityManager, TileMapSystem::home_spawn);

  enemySystem.setMap(entityManager);
  entityManager.addEntity(WavesetManagerFactory::build(waveset_path("waveset0.txt")));

  // Load assets 
  LevelAssetsSystem::getInstance().set_level(level);
  LevelAssetsSystem::getInstance().set_resources(entityManager);

  entityManager.addEntity(BackgroundEntityFactory::createBackgroundEntity(
    LevelAssetsSystem::getInstance().getBgImageFileName(level), false, vec2(2048, 1500)));
  entityManager.addEntity(TowerUiEntityFactory::create());

  particleSystem.initParticleSystem(entityManager); // adds particle entities pool
  renderToTextureSystem.initWaterEffect();
}

World::~World()
{
  HUD::getInstance().reset();
  WavesetSystem::getInstance().reset();
}

void World::reset()
{
  // Load data
  TowerDataLoader::loadTowerData();
  PlayerDataLoader::loadPlayerData();

  // Reset singletons
  HUD::getInstance().reset();
  AudioLoader::getInstance().reset();
  WavesetSystem::getInstance().reset();

  // Remove all recyclable entities
  entityManager.filterRemoveByComponentType(non_recyclable_components);

  // Reset map tower data
  map->getComponent<MapComponent>()->reset();
  // Reset particles pool
  particleSystem.resetParticles(entityManager);
  // Reset home health to max., reset to default texture
  home->getComponent<HealthComponent>()->reset();
  homeSystem.reset(entityManager);
  // Reset player position and wallet
  entityManager.addEntity(PlayerFactory::build(TileMapSystem::player_spawn));

  // Spawn starting resources
  ResourceFactory::spawnInitial(entityManager, TileMapSystem::home_spawn);
  entityManager.addEntity(TowerUiEntityFactory::create());

  paused = false;
  HelpMenu::getInstance().showHelp = false;
  GameOverMenu::getInstance().reset();
}

void World::processInput(float dt, GLboolean keys[], GLboolean keysProcessed[])
{
  // Reset anytime
  if (keys[GLFW_KEY_R] && !keysProcessed[GLFW_KEY_R])
  {
    reset();
    keysProcessed[GLFW_KEY_R] = true;
    return;
  }
  // Change music anytime
  if (keys[GLFW_KEY_M] && !keysProcessed[GLFW_KEY_M])
  {
    AudioLoader::getInstance().changeBgm();
    keysProcessed[GLFW_KEY_M] = true;
  }
  // Pause and unpause anytime
  if (keys[GLFW_KEY_H] && !keysProcessed[GLFW_KEY_H])
  {
    paused = !paused;
    Mix_PlayChannel(-1, AudioLoader::getInstance().pause, 0);
    HelpMenu::getInstance().showHelp = paused;
    if (!HelpMenu::getInstance().showHelp) {
      HelpMenu::getInstance().showTowerHelp = false;
    }
    keysProcessed[GLFW_KEY_H] = true;
  }

  if (paused) { // Only when pause--help menu showing
    if (keys[GLFW_KEY_RIGHT] && !keysProcessed[GLFW_KEY_RIGHT])
    {
      if (HelpMenu::getInstance().showHelp) {
        if (!HelpMenu::getInstance().showTowerHelp) {
          Mix_PlayChannel(-1, AudioLoader::getInstance().next, 0);
        }
        HelpMenu::getInstance().showTowerHelp = true;
      }
      keysProcessed[GLFW_KEY_RIGHT] = true;
    }
    if (keys[GLFW_KEY_LEFT] && !keysProcessed[GLFW_KEY_LEFT])
    {
      if (HelpMenu::getInstance().showTowerHelp) {
        if (HelpMenu::getInstance().showTowerHelp) {
          Mix_PlayChannel(-1, AudioLoader::getInstance().next, 0);
        }
        HelpMenu::getInstance().showTowerHelp = false;
        //HelpMenu::getInstance().showHelp = true;
      }
      keysProcessed[GLFW_KEY_LEFT] = true;
    }

    // In game scene will quit to main menu only when game is paused
    if (keys[GLFW_KEY_ESCAPE] && !keysProcessed[GLFW_KEY_ESCAPE])
    {
      if (shared_ptr<SceneManager> sceneManager_ptr = sceneManager.lock()) {
        sceneManager_ptr->setNextSceneToMainMenu();
      }
      paused = false;
      HelpMenu::getInstance().showHelp = false;
      keysProcessed[GLFW_KEY_ESCAPE] = true;
    }
  }

  if (paused) return; // Don't process the rest if paused

  playerSystem.interpInput(entityManager, dt, keys, keysProcessed);
  towerUiSystem.interpInput(entityManager, keys, keysProcessed);
}

void World::update(float dt)
{
  if (dt >= 0.05) dt = 0.05;
  if (paused) return;
  if (hasWon && level < 5) {
    // Go to next level if not at last level
    auto sceneManager_spt = sceneManager.lock();
    if (level >= sceneManager_spt->levelReached) {
      sceneManager_spt->levelReached = level + 1;
    }
    LevelAssetsSystem::getInstance().set_level(level + 1);
    sceneManager_spt->setNextSceneToInGame(level + 1);
    return;
  }

  // Note: Be careful, order may matter in some cases for systems
  HUD::getInstance().update(dt);

  if(HUD::getInstance().game_over) {
    paused = true;
  }

  hasWon = WavesetSystem::getInstance().handleBuildAndDefensePhase(entityManager, dt);
  if (hasWon) HUD::getInstance().you_win = true;

  enemySystem.move(dt, entityManager);
  physicsSystem.moveEntities(entityManager, dt);
  physicsSystem.rotateEntities(entityManager, dt);
	meshSystem.updateMeshCollision(entityManager);
  interpolationSystem.update(entityManager, dt);
  collisionSystem.checkCollisions(entityManager);
  spriteSystem.updateElapsedTime(dt);
  stateSystem.handleStateChanges(entityManager, dt);

  // Background Update
  backgroundSystem.update(entityManager);

  // Build Tower UI
  towerUiSystem.update(entityManager, dt);

  // Towers
  towerAttackSystem.checkRangeAndShootProjectiles(entityManager);
  towerAttackSystem.reduceElapsedTimeToNextFire(entityManager, dt);

  // Remove entities
  offscreenGarbageSystem.destroyEntitiesContaining(entityManager, vector<int>{ComponentType::projectile});
  offscreenGarbageSystem.destroyEntitiesContaining(entityManager, vector<int>{ComponentType::resource});
  resourceSystem.handleResourceSpawnAndDespawn(entityManager, dt);
  homeSystem.checkState(entityManager);
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
	meshSystem.drawMeshes(entityManager, projection);
  // so far everything rendered into buffer
  // add effects to the buffer and render this buffer to screen
  renderToTextureSystem.drawWaterEffect(entityManager, projection);

  billboardSystem.drawBillboards(entityManager, projection);
  towerRangeDisplaySystem.drawRanges(entityManager, projection);
  towerUiSystem.render(entityManager, projection);
  HUD::getInstance().draw();
  HelpMenu::getInstance().draw(projection);
  GameOverMenu::getInstance().draw(projection);
}
