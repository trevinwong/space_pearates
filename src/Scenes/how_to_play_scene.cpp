#include "how_to_play_scene.hpp"

HowToPlayScene::HowToPlayScene(std::weak_ptr<SceneManager> _sceneManager) : AbstractScene(_sceneManager) {
  projection = glm::ortho(0.0f, static_cast<GLfloat>(SCREEN_WIDTH), static_cast<GLfloat>(SCREEN_HEIGHT), 0.0f, -1.0f, 1.0f);

  Entity bg = BackgroundEntityFactory::createBackgroundEntity("how_to_play_bg.jpg", false, vec2(SCREEN_WIDTH, SCREEN_HEIGHT));
  entityManager.addEntity(bg);

  HelpMenu::getInstance().showHelp = true;
}

void HowToPlayScene::processInput(float dt, GLboolean keys[], GLboolean keysProcessed[]) {
  if (keys[GLFW_KEY_ESCAPE] && !keysProcessed[GLFW_KEY_ESCAPE])
  {
    if(shared_ptr<SceneManager> sceneManager_ptr = sceneManager.lock()){
      HelpMenu::getInstance().showHelp = false;
      sceneManager_ptr->setNextSceneToMainMenu();
    }
    keysProcessed[GLFW_KEY_ESCAPE] = true;
  }
}

void HowToPlayScene::update(float dt) {}

void HowToPlayScene::draw() {
  backgroundSystem.render(entityManager, projection);
}