#ifndef LEVEL_SELECTION_SCENE_H
#define LEVEL_SELECTION_SCENE_H

#include "Utility/utility.hpp"
#include "abstract_scene.hpp"

#include "EntityFactories/background_entity_factory.hpp"
#include "EntityFactories/menu_ui_factory.hpp"
#include "Systems/background_system.hpp"
#include "Systems/menu_ui_system.hpp"
#include "scene_manager.hpp"

class LevelSelectionScene : public AbstractScene {
public:
  LevelSelectionScene(std::weak_ptr<SceneManager> _sceneManager);

  void processInput(float dt, GLboolean keys[], GLboolean keysProcessed[]);

  void update(float dt);

  void draw();

private:
  BackgroundSystem backgroundSystem;
  MenuUiSystem menuUiSystem;
};

#endif //LEVEL_SELECTION_SCENE_H
