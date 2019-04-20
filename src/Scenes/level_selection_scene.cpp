#include "level_selection_scene.hpp"

LevelSelectionScene::LevelSelectionScene(std::weak_ptr<SceneManager> _sceneManager) : AbstractScene(_sceneManager) {
  projection = glm::ortho(0.0f, static_cast<GLfloat>(SCREEN_WIDTH), static_cast<GLfloat>(SCREEN_HEIGHT), 0.0f, -1.0f, 1.0f);

  Entity bg = BackgroundEntityFactory::createBackgroundEntity("level_selection_bg.jpg", false, vec2(SCREEN_WIDTH, SCREEN_HEIGHT));
  entityManager.addEntity(bg);

  Entity menuUi = MenuUiFactory::createLevelSelectionUi(_sceneManager.lock()->getLevelReached());
  entityManager.addEntity(menuUi);
}

void LevelSelectionScene::processInput(float dt, GLboolean keys[], GLboolean keysProcessed[]) {
  vector<shared_ptr<Entity>> menuUiEntities =
      entityManager.getEntities(entityManager.getComponentChecker(vector<int>{ComponentType::menu_ui}));
  if (menuUiEntities.size() == 0) return;

  for (shared_ptr<Entity> menuUi : menuUiEntities) {
    auto sceneManager_spt = sceneManager.lock();
    shared_ptr<MenuUiComponent> menuUiComponent = menuUi->getComponent<MenuUiComponent>();
    if (keys[GLFW_KEY_DOWN] && !keysProcessed[GLFW_KEY_DOWN]) {
      menuUiComponent->selectNext();
      keysProcessed[GLFW_KEY_DOWN] = true;
    } else if (keys[GLFW_KEY_UP] && !keysProcessed[GLFW_KEY_UP]) {
      menuUiComponent->selectPrev();
      keysProcessed[GLFW_KEY_UP] = true;
    } else if (keys[GLFW_KEY_ESCAPE] && !keysProcessed[GLFW_KEY_ESCAPE]) {
      sceneManager_spt->setNextSceneToMainMenu();
      keysProcessed[GLFW_KEY_ESCAPE] = true;
    } else if (keys[GLFW_KEY_ENTER] && !keysProcessed[GLFW_KEY_ENTER] && sceneManager_spt) {
      keysProcessed[GLFW_KEY_ENTER] = true;
      MenuUiComponent::MenuUiChoice selected = menuUiComponent->getSelected();
      switch (selected.choice) {
        case LevelSelectionUiList::level1:
          sceneManager_spt->setNextSceneToInGame(1);
          break;
        case LevelSelectionUiList::level2:
          sceneManager_spt->setNextSceneToInGame(2);
          break;
        case LevelSelectionUiList::level3:
          sceneManager_spt->setNextSceneToInGame(3);
          break;
        case LevelSelectionUiList::level4:
          sceneManager_spt->setNextSceneToInGame(4);
          break;
        case LevelSelectionUiList::level5:
          sceneManager_spt->setNextSceneToInGame(5);
          break;
        case LevelSelectionUiList::back:
          sceneManager_spt->setNextSceneToMainMenu();
          break;
        default:
          break;
      }
    }
  }
}

void LevelSelectionScene::update(float dt) {}

void LevelSelectionScene::draw() {
  backgroundSystem.render(entityManager, projection);
  menuUiSystem.render(entityManager, projection);
}
