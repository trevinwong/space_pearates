#include "scene_manager.hpp"

SceneManager::SceneManager() {
  lastFrame = glfwGetTime();
  currentScene = nullptr;
  nextScene = nullptr;
}

void SceneManager::update(GLboolean keys[], GLboolean keysProcessed[]) {
  trySwapToNextScene();

  // Calculate dT.
  GLfloat currentFrame = glfwGetTime();
  GLfloat deltaTime = currentFrame - lastFrame;
  lastFrame = currentFrame;

  currentScene->processInput(deltaTime, keys, keysProcessed);
  currentScene->update(deltaTime);
  currentScene->draw();
}

void SceneManager::terminateAndCloseWindow() {
  if (window) glfwSetWindowShouldClose(window, GL_TRUE);
}

void SceneManager::setGLFWwindow(GLFWwindow *_window) {
  if (_window) window = _window;
}

void SceneManager::trySwapToNextScene() {
  if (nextScene != nullptr) {
    currentScene = nextScene;
    nextScene = nullptr;
    lastFrame = glfwGetTime();
  }
}

void SceneManager::setNextSceneToHowToPlay() {
  std::weak_ptr<SceneManager> sceneManager = shared_from_this();
  auto scene = make_shared<HowToPlayScene>(sceneManager);
  nextScene = std::dynamic_pointer_cast<AbstractScene>(scene);
}

void SceneManager::setNextSceneToInGame(int level) {
  showLoadingScreenNow();
  Mix_PlayChannel(-1, AudioLoader::getInstance().start, 0);
  std::weak_ptr<SceneManager> sceneManager = shared_from_this();
  auto scene = make_shared<World>(sceneManager);
  nextScene = std::dynamic_pointer_cast<AbstractScene>(scene);
}

void SceneManager::setNextSceneToLevelSelection() {
  std::weak_ptr<SceneManager> sceneManager = shared_from_this();
  auto scene = make_shared<LevelSelectionScene>(sceneManager);
  nextScene = std::dynamic_pointer_cast<AbstractScene>(scene);
}

void SceneManager::setNextSceneToMainMenu() {
  std::weak_ptr<SceneManager> sceneManager = shared_from_this();
  auto scene = make_shared<MainMenuScene>(sceneManager);
  nextScene = std::dynamic_pointer_cast<AbstractScene>(scene);
}

void SceneManager::showLoadingScreenNow() {
  std::weak_ptr<SceneManager> sceneManager = shared_from_this();
  auto scene = make_shared<LoadingScene>(sceneManager);
  currentScene = std::dynamic_pointer_cast<AbstractScene>(scene); // replace currentScene directly

  // draw on both buffers, otherwise a flash screen bug appears
  currentScene->draw();
  glfwSwapBuffers(window);
  glfwPollEvents();

  currentScene->draw();
  glfwSwapBuffers(window);
  glfwPollEvents();
}
