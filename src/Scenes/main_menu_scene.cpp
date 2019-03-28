#include "main_menu_scene.hpp"

MainMenuScene::MainMenuScene(std::weak_ptr<SceneManager> _sceneManager) : AbstractScene(_sceneManager) {
  projection = glm::ortho(0.0f, static_cast<GLfloat>(SCREEN_WIDTH), static_cast<GLfloat>(SCREEN_HEIGHT), 0.0f, -1.0f, 1.0f);

  Entity bg = BackgroundEntityFactory::createBackgroundEntity("main_menu_bg.jpg", false, vec2(SCREEN_WIDTH, SCREEN_HEIGHT));
  entityManager.addEntity(bg);

  Entity menuUi = MenuUiFactory::createMainMenuUi();
  entityManager.addEntity(menuUi);
}

void MainMenuScene::processInput(float dt, GLboolean keys[], GLboolean keysProcessed[]) {
  vector<shared_ptr<Entity>> menuUiEntities =
    entityManager.getEntities(entityManager.getComponentChecker(vector<int>{ComponentType::menu_ui}));
  if (menuUiEntities.size() == 0) return;

  for (shared_ptr<Entity> menuUi : menuUiEntities) {
    shared_ptr<MenuUiComponent> menuUiComponent = menuUi->getComponent<MenuUiComponent>();
    if (keys[GLFW_KEY_DOWN] && !keysProcessed[GLFW_KEY_DOWN]) {
      menuUiComponent->selectNext();
      keysProcessed[GLFW_KEY_DOWN] = true;
    }
    else if (keys[GLFW_KEY_UP] && !keysProcessed[GLFW_KEY_UP]) {
      menuUiComponent->selectPrev();
      keysProcessed[GLFW_KEY_UP] = true;
    }
    else if (keys[GLFW_KEY_ENTER] && !keysProcessed[GLFW_KEY_ENTER]) {
      keysProcessed[GLFW_KEY_ENTER] = true;
      shared_ptr<SceneManager> sceneManager_spt = sceneManager.lock();
      if (sceneManager_spt) {
        MenuUiComponent::MenuUiChoice selected = menuUiComponent->getSelected();
        switch (selected.choice) {
        case MainMenuUiList::how_to_play:
          sceneManager_spt->setNextSceneToHowToPlay();
          break;
        case MainMenuUiList::new_game: {
          sceneManager_spt->setNextSceneToInGame(1); // level 1
          break;
        }
        case MainMenuUiList::continue_game:
          break;
        case MainMenuUiList::level_selection:
          sceneManager_spt->setNextSceneToLevelSelection();
          break;
        case MainMenuUiList::exit:
          sceneManager_spt->terminateAndCloseWindow();
          break;
        default:
          break;
        }
      }
    }
  }
}

void MainMenuScene::update(float dt) {}

void MainMenuScene::draw() {
  backgroundSystem.render(entityManager, projection);
  menuUiSystem.render(entityManager, projection);
}