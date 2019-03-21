#ifndef MENU_UI_SYSTEM_H
#define MENU_UI_SYSTEM_H

#include "../Utility/utility.hpp"
#include "../entity_manager.hpp"
#include "../Utility/text.hpp"
//#include "Scenes/scene_manager.hpp"
#include "Components/MenuUI/menu_ui_component.hpp"

class MenuUiSystem {
public:
  void render(EntityManager &entityManager, glm::mat4 projection);

private:

};

#endif // !MENU_UI_SYSTEM
