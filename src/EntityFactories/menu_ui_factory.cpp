#include "menu_ui_factory.hpp"

Entity MenuUiFactory::createMainMenuUi() {

  vector<MenuUiComponent::MenuUiChoice> choices =
      {
          {MainMenuUiList::how_to_play,     "How to Play",     true},
          {MainMenuUiList::new_game,        "New Game",        true},
          {MainMenuUiList::continue_game,   "Continue",        false},
          {MainMenuUiList::level_selection, "Level Selection", true},
          {MainMenuUiList::exit,            "EXIT",            true}
      };

  vec2 position = vec2(SCREEN_WIDTH - 350, SCREEN_HEIGHT - 270);
  float marginInBtw = 2.0f;  //left, top, right, bottom
  float fontScale = 1.0f;
  vec3 fontColor = vec3(1.f, 1.f, 1.f);
  vec3 unavaliableFontColor = vec3(0.4f, 0.4f, 0.4f);
  float selectedFontScale = 1.0f;
  vec3 selectedFontColor = vec3(1.f, 0.f, 0.f);
  int fontFamily = Text::Font::munro;

  shared_ptr<MenuUiComponent> menuUi = make_shared<MenuUiComponent>();
  menuUi->choices = choices;
  menuUi->selectNext(); // default selection is "New Game"
  menuUi->position = position;
  menuUi->marginInBtw = marginInBtw;
  menuUi->fontScale = fontScale;
  menuUi->fontColor = fontColor;
  menuUi->unavaliableFontColor = unavaliableFontColor;
  menuUi->selectedFontScale = selectedFontScale;
  menuUi->selectedFontColor = selectedFontColor;
  menuUi->fontFamily = fontFamily;

  Entity e;
  e.setComponent<MenuUiComponent>(menuUi);
  return e;
}

Entity MenuUiFactory::createLevelSelectionUi() {

  // TODO: read from file
  int levelReached = 1;

  vector<MenuUiComponent::MenuUiChoice> choices =
      {
          {LevelSelectionUiList::level1,    "Level 1", LevelSelectionUiList::level1 <= levelReached},
          {LevelSelectionUiList::level2,    "Level 2", LevelSelectionUiList::level2 <= levelReached},
          {LevelSelectionUiList::level3,    "Level 3", LevelSelectionUiList::level3 <= levelReached},
          {LevelSelectionUiList::level4,    "Level 4", LevelSelectionUiList::level4 <= levelReached},
          {LevelSelectionUiList::bosslevel, "BOSS",    LevelSelectionUiList::bosslevel <= levelReached},
          {LevelSelectionUiList::back,      "Back",    true}

      };

  vec2 position = vec2(SCREEN_WIDTH - 350, SCREEN_HEIGHT - 300);
  float marginInBtw = 2.0f;  //left, top, right, bottom
  float fontScale = 1.0f;
  vec3 fontColor = vec3(1.f, 1.f, 1.f);
  vec3 unavaliableFontColor = vec3(0.4f, 0.4f, 0.4f);
  float selectedFontScale = 1.0f;
  vec3 selectedFontColor = vec3(1.f, 0.f, 0.f);
  int fontFamily = Text::Font::munro;

  shared_ptr<MenuUiComponent> menuUi = make_shared<MenuUiComponent>();
  menuUi->choices = choices;
  menuUi->position = position;
  menuUi->marginInBtw = marginInBtw;
  menuUi->fontScale = fontScale;
  menuUi->fontColor = fontColor;
  menuUi->unavaliableFontColor = unavaliableFontColor;
  menuUi->selectedFontScale = selectedFontScale;
  menuUi->selectedFontColor = selectedFontColor;
  menuUi->fontFamily = fontFamily;

  Entity e;
  e.setComponent<MenuUiComponent>(menuUi);
  return e;
}
