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
  string loadingScreenTextures[3] = {
    "loading_screen_tips0.jpg", 
    "loading_screen_tips1.jpg",
    "loading_screen_tips2.jpg"
  };

  BackgroundSystem backgroundSystem;
};


#endif // LOADING_SCENE_H
