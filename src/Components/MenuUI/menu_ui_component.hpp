#ifndef MENU_UI_COMPONENT
#define MENU_UI_COMPONENT

#include <Components/base_component.hpp>
#include "../../Utility/utility.hpp"

namespace MainMenuUiList {
  enum MainMenuUiList {
    how_to_play,
    new_game,
    continue_game,
    level_selection,
    exit,
    max_count
  };
}

namespace LevelSelectionUiList {
  enum LevelSelectionUiList {
    level0_place_holder,
    level1,
    level2,
    level3,
    level4,
    level5,
    back,
    max_count
  };
}

class MenuUiComponent : public BaseComponent {
public:
  struct MenuUiChoice {
    int choice;
    string choiceContext;
    bool isAvaliable;
  };
  vector<MenuUiChoice> choices;
  vec2 position;
  float marginInBtw;  //margin between each choice
  float fontScale;
  glm::vec4 fontColor;
  glm::vec4 unavaliableFontColor;
  float selectedFontScale;
  glm::vec4 selectedFontColor;
  int fontFamily;

  MenuUiChoice getSelected();
  int getSelectedIndex();
  void selectNext();
  void selectPrev();

  static const int typeID = ComponentType::menu_ui;
  inline virtual int getTypeID() const { return typeID; };
private:
  int currentSelected;
};

#endif // !MENU_UI_COMPONENT
