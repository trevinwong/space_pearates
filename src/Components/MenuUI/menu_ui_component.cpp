#include "menu_ui_component.hpp"

MenuUiComponent::MenuUiChoice MenuUiComponent::getSelected() {
  return choices[getSelectedIndex()];
}

int MenuUiComponent::getSelectedIndex() {
  int numberOfChoices = choices.size();
  int selectedIndex = (currentSelected % numberOfChoices + numberOfChoices) % numberOfChoices;
  return selectedIndex;
}

void MenuUiComponent::selectNext() {
  int numberOfChoices = choices.size();
  while(true) {
    int newSelectedIndex = ((currentSelected + 1) % numberOfChoices + numberOfChoices) % numberOfChoices;
    currentSelected = newSelectedIndex;
    if (choices[newSelectedIndex].isAvaliable) return;
  }
}

void MenuUiComponent::selectPrev() {
  int numberOfChoices = choices.size();
  while(true) {
    int newSelectedIndex = ((currentSelected - 1) % numberOfChoices + numberOfChoices) % numberOfChoices;
    currentSelected = newSelectedIndex;
    if (choices[newSelectedIndex].isAvaliable) return;
  }
}
