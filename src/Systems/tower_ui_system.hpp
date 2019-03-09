#ifndef TOWER_UI_SYSTEM_H
#define TOWER_UI_SYSTEM_H

#include <algorithm>
#include "../utility.hpp"
#include "../entity.hpp"
#include "../entity_manager.hpp"
#include "event_system.hpp"
#include "../EntityFactories/tower_entity_factory.hpp"
#include "../Components/sprite_component.hpp"
#include "../Components/transform_component.hpp"
#include "../Components/map_component.hpp"
//#include "../Components/TowerUI/build_tower_ui_component.hpp"
//#include "../Components/TowerUI/operate_tower_ui_component.hpp"
#include "../Components/TowerUI/tower_ui_button_component.hpp"
#include "../Components/TowerUI/tower_ui_button_meta_component.hpp"
#include "../Components/TowerUI/TowerUIState/tower_ui_state_component.hpp"

class TowerUiSystem {
public:
  void interpInput(EntityManager& entityManager, GLboolean keys[], GLboolean keysProcessed[]);
  void update(EntityManager& entityManager, float dt);
  void render(EntityManager& entityManager, glm::mat4 projection);
private:
  void renderTowerUiButtons(TowerUiButtonMetaComponent *towerUiButtonMeta, TowerUiButtonComponent *towerUiButton, glm::mat4 projection);
  void renderDescription(TowerUiButtonMetaComponent *towerUiButtonMeta, TowerUiButtonComponent *towerUiButton,  glm::mat4 projection);
};

#endif // !TOWER_UI_SYSTEM_H
