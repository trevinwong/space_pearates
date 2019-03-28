#include "loading_scene.hpp"

LoadingScene::LoadingScene(std::weak_ptr<SceneManager> _sceneManager) : AbstractScene(_sceneManager) {
  projection = glm::ortho(0.0f, static_cast<GLfloat>(SCREEN_WIDTH), static_cast<GLfloat>(SCREEN_HEIGHT), 0.0f, -1.0f, 1.0f);

  int numberOfloadingScreenTextures = sizeof(loadingScreenTextures)/sizeof(loadingScreenTextures[0]);

  srand(time(NULL));
  int selectedTipIndex = rand() % numberOfloadingScreenTextures;
  string loadingScreenTextureFileName = loadingScreenTextures[selectedTipIndex];
  Entity bg = BackgroundEntityFactory::createBackgroundEntity(loadingScreenDir + loadingScreenTextureFileName, false, vec2(SCREEN_WIDTH, SCREEN_HEIGHT));
  entityManager.addEntity(bg);
}

void LoadingScene::processInput(float dt, GLboolean keys[], GLboolean keysProcessed[]) {
  // no input for loading screen
}

void LoadingScene::update(float dt) {
  // no update for loading screen
}

void LoadingScene::draw() {
  backgroundSystem.render(entityManager, projection);

  string loadingStr = "Loading...";
  vec2 loadingStrPos = vec2(SCREEN_WIDTH - 300.0, SCREEN_HEIGHT - 50.0);
  vec3 loadingStrColor = vec3(1.0, 1.0, 1.0);
  int fontFamily = Text::Font::munro;
  Text::getInstance().render(loadingStr, loadingStrPos, 1.0, loadingStrColor, fontFamily);
}
