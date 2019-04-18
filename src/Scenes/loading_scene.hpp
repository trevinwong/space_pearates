#ifndef LOADING_SCENE_H
#define LOADING_SCENE_H

#include <time.h>
#include "Utility/utility.hpp"
#include "abstract_scene.hpp"

#include "EntityFactories/background_entity_factory.hpp"
#include "EntityFactories/menu_ui_factory.hpp"
#include "Systems/background_system.hpp"
#include "scene_manager.hpp"

class LoadingScene : public AbstractScene {
public:
  LoadingScene(std::weak_ptr<SceneManager> _sceneManager);

  void processInput(float dt, GLboolean keys[], GLboolean keysProcessed[]);

  void update(float dt);

  void draw();

private:
  string loadingScreenDir = "loading_screens/";
  string loadingScreenTextures[11] = {
    "loading_screen_tips0.jpg", 
    "loading_screen_tips1.jpg",
    "loading_screen_tips2.jpg",
    "loading_screen_tips3.jpg",
    "loading_screen_tips4.jpg",
    "loading_screen_tips5.jpg",
    "loading_screen_tips6.jpg",
    "loading_screen_tips7.jpg",
    "loading_screen_tips8.jpg",
    "loading_screen_tips9.jpg",
    "loading_screen_tips10.jpg"
  };

  BackgroundSystem backgroundSystem;
};


#endif // LOADING_SCENE_H
