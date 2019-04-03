#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "Utility/utility.hpp"
#include "abstract_scene.hpp"

#include "world.hpp"
#include "level_selection_scene.hpp"
#include "main_menu_scene.hpp"
#include "how_to_play_scene.hpp"
#include "tutorial_scene.hpp"
#include "loading_scene.hpp"

class SceneManager : public std::enable_shared_from_this<SceneManager> {
public:
  SceneManager();
  ~SceneManager();

  void update(GLboolean keys[], GLboolean keysProcessed[]);

  void terminateAndCloseWindow();

  void setNextSceneToHowToPlay();

  void setNextSceneToTutorial();

  void setNextSceneToInGame(int level);

  void setNextSceneToLevelSelection();

  void setNextSceneToMainMenu();

  void showLoadingScreenNow();

  void setGLFWwindow(GLFWwindow *window);

  int levelReached = 1;

private:
  /* 
    Why we need to store prevScene?
    Usually the scene will be changed in the meanwhile some scene, i.e. a new scene changed in the update() or input()
    However, this means this scene is still on-the-fly.
    If currentScene pointer is changed directly, e.g. in showLoadingScreenNow(), then no pointer will point to this scene
    and this scene will be destroyed by smart pointer automatically, then crash
    Therefore, use prevScene pointer points to this part of memory for a while until next scene is fully ready to swap.
  */ 
  shared_ptr<AbstractScene> prevScene;
  shared_ptr<AbstractScene> currentScene;
  shared_ptr<AbstractScene> nextScene;
  GLfloat lastFrame;
  GLFWwindow *window;

  // if nextScene is ready, then swap to next world
  void trySwapToNextScene();

  int readLevelReached();
};

#endif // !SCENE_MANAGER_H
