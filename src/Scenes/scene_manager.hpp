#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "Utility/utility.hpp"
#include "abstract_scene.hpp"

#include "world.hpp"
#include "level_selection_scene.hpp"
#include "main_menu_scene.hpp"
#include "how_to_play_scene.hpp"
#include "loading_scene.hpp"

class SceneManager : public std::enable_shared_from_this<SceneManager> {
public:
  SceneManager();

  void update(GLboolean keys[], GLboolean keysProcessed[]);

  void terminateAndCloseWindow();

  void setNextSceneToHowToPlay();

  void setNextSceneToInGame(int level);

  void setNextSceneToLevelSelection();

  void setNextSceneToMainMenu();

  void showLoadingScreenNow();

  void setGLFWwindow(GLFWwindow *window);

private:
  shared_ptr<AbstractScene> currentScene;
  shared_ptr<AbstractScene> nextScene;
  GLfloat lastFrame;
  GLFWwindow *window;

  // if nextScene is ready, then swap to next world
  void trySwapToNextScene();
};

#endif // !SCENE_MANAGER_H
