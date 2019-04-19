#include "how_to_play_scene.hpp"

HowToPlayScene::HowToPlayScene(std::weak_ptr<SceneManager> _sceneManager) : AbstractScene(_sceneManager) {
  projection = glm::ortho(0.0f, static_cast<GLfloat>(SCREEN_WIDTH), static_cast<GLfloat>(SCREEN_HEIGHT), 0.0f, -1.0f, 1.0f);

  Entity bg = BackgroundEntityFactory::createBackgroundEntity("main_menu_bg.jpg", false, vec2(SCREEN_WIDTH, SCREEN_HEIGHT));
  entityManager.addEntity(bg);

  HelpMenu::getInstance().showHelp = true;
}

void HowToPlayScene::processInput(float dt, GLboolean keys[], GLboolean keysProcessed[]) {
  // FIXME: eww lots of duplicated code with different scenes/worlds
  if (keys[GLFW_KEY_H] && !keysProcessed[GLFW_KEY_H])
  {
    if(shared_ptr<SceneManager> sceneManager_ptr = sceneManager.lock()){
      HelpMenu::getInstance().showHelp = false;
      sceneManager_ptr->setNextSceneToMainMenu();
    }
    keysProcessed[GLFW_KEY_H] = true;
  }

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

}

void HowToPlayScene::update(float dt) {}

void HowToPlayScene::draw() {
  backgroundSystem.render(entityManager, projection);
  HelpMenu::getInstance().draw(projection);
}