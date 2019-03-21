#ifndef MENU_UI_FACTORY_HPP
#define MENU_UI_FACTORY_HPP

#include <cassert>
#include <entity.hpp>
#include <Utility/text.hpp>
#include <Utility/utility.hpp>
#include "../Components/MenuUI/menu_ui_component.hpp"

class MenuUiFactory{
public:
  static Entity createMainMenuUi();

  /*
   * e.g. levelReached = 3, which means the player has passed level1, 2 and 3
   */
  static Entity createLevelSelectionUi();
private:
  MenuUiFactory();
};

#endif //MENU_UI_FACTORY_HPP
