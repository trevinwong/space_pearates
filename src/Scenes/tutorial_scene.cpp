#include "tutorial_scene.hpp"

TutorialScene::TutorialScene(std::weak_ptr<SceneManager> _sceneManager) : AbstractScene(_sceneManager)
{
  currentStep = TutorialStep::prologue;
  AudioLoader::getInstance().playGameMusic();

  vec2 screen = vec2(SCREEN_WIDTH, SCREEN_HEIGHT);
  TowerDataLoader::loadTowerData();
  PlayerDataLoader::loadPlayerData();
  projection = glm::ortho(0.0f, static_cast<GLfloat>(screen.x), static_cast<GLfloat>(screen.y), 0.0f, -1.0f, 1.0f);
  physicsSystem.setScreenInfo(screen);
  collisionSystem.setScreenInfo(screen);
  entityManager = EntityManager();

  string mapName = "tutorial.txt";
  shared_ptr<Entity> map = make_shared<Entity>(MapEntityFactory::createMapEntityFromFile(map_path() + mapName));
  entityManager.addEntity(map);

  TileMapSystem::loadTileMap(entityManager, true);
  shared_ptr<Entity> player = make_shared<Entity>(PlayerFactory::build(TileMapSystem::player_spawn));
  entityManager.addEntity(player);

  Entity coin = ResourceFactory::build(vec2(320.0f, SCREEN_HEIGHT - 100.0f));
  coin.removeComponent<MovementComponent>(); // remove gravity to avoid the coin falls down
  entityManager.addEntity(coin);

  entityManager.addEntity(BackgroundEntityFactory::createBackgroundEntity("earth_bg.png", false, vec2(2304, 1620)));

  // remove water tower from tutorial
  Entity towerUi = TowerUiEntityFactory::create();
  auto towerUiButtonMeta = towerUi.getComponent<TowerUiButtonMetaComponent>();
  if (towerUiButtonMeta) {
    auto buildOptList = &towerUiButtonMeta->buildOptList;
    buildOptList->erase(std::remove(buildOptList->begin(), buildOptList->end(), BUILD_WATER_TOWER), buildOptList->end());
  }
  entityManager.addEntity(towerUi);

  particleSystem.initParticleSystem(entityManager); // adds particle entities pool

  Entity simpleSprite = SimpleSpriteFactory::create("/tutorial_scene/prologue.png", true, vec2(0.f, 0.f), vec2(1280.0f, 800.0f), vec4(1, 1, 1, 1));
  tutorialIndicator = make_shared<Entity>(simpleSprite);
  entityManager.addEntity(tutorialIndicator);

  HelpMenu::getInstance().showHelp = false;

  renderToTextureSystem.initWaterEffect();
}

TutorialScene::~TutorialScene()
{
  HUD::getInstance().reset();
}

void TutorialScene::processInput(float dt, GLboolean keys[], GLboolean keysProcessed[])
{
  // pause and help menu process
  if (keys[GLFW_KEY_H] && !keysProcessed[GLFW_KEY_H])
  {
    paused = !paused;
    Mix_PlayChannel(-1, AudioLoader::getInstance().pause, 0);
    HelpMenu::getInstance().showHelp = paused;
    keysProcessed[GLFW_KEY_H] = true;
  }
  // In game scene will quit to main menu only when game is paused
  if (paused && keys[GLFW_KEY_ESCAPE] && !keysProcessed[GLFW_KEY_ESCAPE])
  {
    keysProcessed[GLFW_KEY_ESCAPE] = true;
    paused = false;
    HelpMenu::getInstance().showHelp = false;
    if (shared_ptr<SceneManager> sceneManager_ptr = sceneManager.lock())
      sceneManager_ptr->setNextSceneToMainMenu();
  }
  if (paused) return;

  tutorialInputProcess(dt, keys, keysProcessed);

  playerSystem.interpInput(entityManager, dt, keys, keysProcessed);
  towerUiSystem.interpInput(entityManager, keys, keysProcessed);
}

void TutorialScene::update(float dt)
{
  if (paused) return;

  tutorialUpdate(dt);

  if (currentStep != TutorialStep::prologue) HUD::getInstance().update(dt);

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
  // resourceSystem.handleResourceSpawnAndDespawn(entityManager, dt);
  homeSystem.checkState(entityManager);
  particleSystem.updateParticles(entityManager, dt);
  damageSystem.handleDamage(entityManager);
  deathSystem.handleDeaths(entityManager);
}

void TutorialScene::draw()
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
  if (currentStep == TutorialStep::try_to_build_a_tower) towerUiSystem.render(entityManager, projection);
  if (currentStep != TutorialStep::prologue) HUD::getInstance().draw();
  HelpMenu::getInstance().draw(projection);
}

void changeTutorialIndicatorImage(shared_ptr<Entity> tutorialIndicator, string imageFile) {
  std::string imagePath = string(texture_path("")) + "/tutorial_scene/" + imageFile;
  shared_ptr<Texture> hudTutorialTexture = make_shared<Texture>(imagePath.c_str(), true);
  tutorialIndicator->getComponent<SpriteComponent>()->texture = hudTutorialTexture;
}

void TutorialScene::tutorialInputProcess(float dt, GLboolean keys[], GLboolean keysProcessed[])
{
  if (keys[GLFW_KEY_ENTER] && !keysProcessed[GLFW_KEY_ENTER]) {
    keysProcessed[GLFW_KEY_ENTER] = true;
    switch (currentStep) {
    case TutorialStep::prologue:
    {
      currentStep = TutorialStep::hud_tutorial;
      changeTutorialIndicatorImage(tutorialIndicator, "hud_tutorial.png");
      break;
    }
    case TutorialStep::hud_tutorial:
    {
      currentStep = TutorialStep::introduce_elements;
      changeTutorialIndicatorImage(tutorialIndicator, "introduce_elements.png");
      break;
    }
    case TutorialStep::introduce_elements:
    {
      currentStep = TutorialStep::try_to_move_and_pick_up_coins;
      changeTutorialIndicatorImage(tutorialIndicator, "try_to_move_and_pick_up_coins.png");
      break;
    }
    case TutorialStep::learned_move_done:
    {
      // create a sample enemy 
      Entity enemy = EnemyFactory::build(vec2(1200, 670), vec2(0.0f, 0.0f));
      sampleEnemy = make_shared<Entity>(enemy);
      entityManager.addEntity(sampleEnemy);

      currentStep = TutorialStep::an_enemy_is_coming;
      changeTutorialIndicatorImage(tutorialIndicator, "an_enemy_is_coming.png");
      break;
    }
    case TutorialStep::an_enemy_is_coming:
    {
      currentStep = TutorialStep::show_enemy_target;
      changeTutorialIndicatorImage(tutorialIndicator, "show_enemy_target.png");
      break;
    }
    case TutorialStep::show_enemy_target:
    {
      currentStep = TutorialStep::try_to_build_a_tower;
      changeTutorialIndicatorImage(tutorialIndicator, "try_to_build_a_tower.png");
      break;
    }
    case TutorialStep::the_enemy_is_killed:
    {
      currentStep = TutorialStep::tutorial_done;
      changeTutorialIndicatorImage(tutorialIndicator, "tutorial_done.png");
      break;
    }
    case TutorialStep::tutorial_done:
    {
      if (auto sceneManager_spt = sceneManager.lock()) {
        if (sceneManager_spt->getLevelReached() <= 0) sceneManager_spt->incrementLevelReached();
        sceneManager_spt->setNextSceneToInGame(1); // go to level 1
      }
      break;
    }
    default:
      break;
    }
  }

  // player can only move when the tutorial let them move
  if (currentStep != TutorialStep::try_to_move_and_pick_up_coins && currentStep != TutorialStep::try_to_build_a_tower) {
    keys[GLFW_KEY_LEFT] = false;
    keys[GLFW_KEY_RIGHT] = false;
    keys[GLFW_KEY_UP] = false;
    keys[GLFW_KEY_DOWN] = false;
  }
  // play can only build towers when the tutorial let them build
  if (currentStep != TutorialStep::try_to_build_a_tower) {
    keys[GLFW_KEY_S] = false;
    keys[GLFW_KEY_SPACE] = false;
  }
}

void TutorialScene::tutorialUpdate(float dt)
{
  switch (currentStep) {
    // try_to_move_and_pick_up_coins state check
    // all coins (resource) should be picked up
  case TutorialStep::try_to_move_and_pick_up_coins:
  {
    vector<shared_ptr<Entity>> entities =
      entityManager.getEntities(entityManager.getComponentChecker(vector<int>{ComponentType::resource}));
    if (entities.size() <= 0) {
      currentStep = TutorialStep::learned_move_done;
      changeTutorialIndicatorImage(tutorialIndicator, "learned_move_done.png");
    }
    break;
  }
  case TutorialStep::try_to_build_a_tower:
  {
    // check if a tower is build
    vector<shared_ptr<Entity>> towers =
      entityManager.getEntities(entityManager.getComponentChecker(vector<int>{ComponentType::attack_tower}));
    if (towers.size() > 0) {
      sampleEnemy->getComponent<MovementComponent>()->velocity = vec2(-40.0f, 0.0f);

      currentStep = TutorialStep::the_enemy_is_moving;
      changeTutorialIndicatorImage(tutorialIndicator, "the_enemy_is_moving.png");
    }
    break;
  }
  case TutorialStep::the_enemy_is_moving:
  {
    // check if a tower is build
    vector<shared_ptr<Entity>> enemies =
      entityManager.getEntities(entityManager.getComponentChecker(vector<int>{ComponentType::enemy}));
    if (enemies.size() <= 0) {
      currentStep = TutorialStep::the_enemy_is_killed;
      changeTutorialIndicatorImage(tutorialIndicator, "the_enemy_is_killed.png");
    }
  }
  default:
    break;
  }
}
