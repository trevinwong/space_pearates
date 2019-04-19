#include "scene_manager.hpp"

SceneManager::SceneManager() {
  lastFrame = glfwGetTime();
  currentScene = nullptr;
  nextScene = nullptr;

  levelReached = readLevelReached();
}

int SceneManager::readLevelReached()
{
  int level = 1;
  std::ifstream save_file(data_path "save0.txt");
  string line;
  if (save_file.is_open()) {
    // Just get the first line, nothing else saved for now
    if (getline(save_file, line))
    {
      level = stoi(line);
    }
    save_file.close();
  }
  //else cout << "Unable to open file";

  return level;
}

SceneManager::~SceneManager()
{
  saveToDisk();
}

void SceneManager::saveToDisk()
{
  // Save level reached to disk
  std::ofstream save_file(data_path "save0.txt");
  if (save_file.is_open()) {
    save_file << std::to_string(levelReached) << endl;
    save_file.close();
  }
  else cout << "Unable to save file";
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

void SceneManager::incrementLevelReached()
{
  levelReached++;
  saveToDisk();
}

int SceneManager::getLevelReached()
{
  return levelReached;
}

void SceneManager::trySwapToNextScene() {
  if (nextScene != nullptr) {
    currentScene = nextScene;
    nextScene = nullptr;
    prevScene = nullptr;
    lastFrame = glfwGetTime();
  }
}

void SceneManager::setNextSceneToHowToPlay() {
  std::weak_ptr<SceneManager> sceneManager = shared_from_this();
  auto scene = make_shared<HowToPlayScene>(sceneManager);
  nextScene = std::dynamic_pointer_cast<AbstractScene>(scene);
}

void SceneManager::setNextSceneToTutorial() {
  showLoadingScreenNow();
  Mix_PlayChannel(-1, AudioLoader::getInstance().start, 0);
  std::weak_ptr<SceneManager> sceneManager = shared_from_this();
  auto scene = make_shared<TutorialScene>(sceneManager);
  nextScene = std::dynamic_pointer_cast<AbstractScene>(scene);
}

void SceneManager::setNextSceneToInGame(int level) {
  showLoadingScreenNow();
  Mix_PlayChannel(-1, AudioLoader::getInstance().start, 0);
  std::weak_ptr<SceneManager> sceneManager = shared_from_this();
  auto scene = make_shared<World>(sceneManager, level);
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
  // make a backup of prev scene since prev scene is still on flying, to avoid smart pointer auto garbage collection
  prevScene = currentScene;
  currentScene = std::dynamic_pointer_cast<AbstractScene>(scene); // replace currentScene directly

  // draw on both buffers, otherwise a flash screen bug appears
  currentScene->draw();
  glfwSwapBuffers(window);
  glfwPollEvents();

  currentScene->draw();
  glfwSwapBuffers(window);
  glfwPollEvents();
}
