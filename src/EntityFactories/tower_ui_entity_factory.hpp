#ifndef TOWER_UI_ENTITY_FACTORY_H
#define TOWER_UI_ENTITY_FACTORY_H

#include "../Utility/utility.hpp"
#include "../entity.hpp"
#include "../entity_manager.hpp"
#include "../Components/sprite_component.hpp"
#include "../Components/color_component.hpp"
#include "../Components/transform_component.hpp"
#include "../Components/TowerUI/tower_ui_button_component.hpp"
#include "../Components/TowerUI/tower_ui_button_meta_component.hpp"
#include "../Components/TowerUI/TowerUIState/tower_ui_state_component.hpp"
#include "../Components/TowerUI/TowerUIState/tower_ui_idle_state.hpp"

class TowerUiEntityFactory {
  public:
    static Entity create();
  private:
    TowerUiEntityFactory(){};
};

#endif // !TOWER_UI_ENTITY_FACTORY_H
