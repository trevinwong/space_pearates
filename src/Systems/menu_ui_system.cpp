#include "menu_ui_system.hpp"

void MenuUiSystem::render(EntityManager &entityManager, glm::mat4 projection) {
  vector<shared_ptr<Entity>> menuUiEntities =
      entityManager.getEntities(entityManager.getComponentChecker(vector<int>{ComponentType::menu_ui}));
  if (menuUiEntities.size() == 0) return;

  for (shared_ptr<Entity> menuUi : menuUiEntities) {
    shared_ptr<MenuUiComponent> menuUiComponent = menuUi->getComponent<MenuUiComponent>();
    vector<MenuUiComponent::MenuUiChoice> choices = menuUiComponent->choices;
    vec2 position = menuUiComponent->position;

    for (int i = 0; i < choices.size(); i++) {
      if (i == menuUiComponent->getSelectedIndex()) {
        Text::getInstance().render(choices[i].choiceContext, position, menuUiComponent->selectedFontScale, menuUiComponent->selectedFontColor, menuUiComponent->fontFamily);
        position.y += menuUiComponent->marginInBtw;
        position.y += menuUiComponent->selectedFontScale * 50.0f;
      } else if (!choices[i].isAvaliable) {
        Text::getInstance().render(choices[i].choiceContext, position, menuUiComponent->fontScale, menuUiComponent->unavaliableFontColor, menuUiComponent->fontFamily);
        position.y += menuUiComponent->marginInBtw;
        position.y += menuUiComponent->fontScale * 50.0f;
      } else {
        Text::getInstance().render(choices[i].choiceContext, position, menuUiComponent->fontScale, menuUiComponent->fontColor, menuUiComponent->fontFamily);
        position.y += menuUiComponent->marginInBtw;
        position.y += menuUiComponent->fontScale * 50.0f;
      }
    }

  }
}
