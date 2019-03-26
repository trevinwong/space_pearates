#ifndef HOW_TO_PLAY_SCENE_H
#define HOW_TO_PLAY_SCENE_H

#include "Utility/utility.hpp"
#include "abstract_scene.hpp"

#include "EntityFactories/background_entity_factory.hpp"
#include "Systems/background_system.hpp"
#include "scene_manager.hpp"
#include "help_menu.hpp"

class HowToPlayScene : public AbstractScene {
public:
  HowToPlayScene(std::weak_ptr<SceneManager> _sceneManager);

  void processInput(float dt, GLboolean keys[], GLboolean keysProcessed[]);

  void update(float dt);

  void draw();

private:
  BackgroundSystem backgroundSystem;
};


#endif //HOW_TO_PLAY_SCENE_H
