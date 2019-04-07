#include "tower_ui_button_component.hpp"

TowerUiButtonComponent::TowerUiButtonComponent() {
  isDisplay = false;

  tilePosition = vec2(0, 0);
  isTowerHere = false;
  currentSelectedBuildOptIndex = 0;
  currentSelectedOptIndex = 0;

  for (int i = 0; i < TOWER_UI_BUTTON_NUMBER; i++) {
    std::shared_ptr<TowerUiBtn> btn = std::make_shared<TowerUiBtn>();
    btn->relativeIndex = i - 1; //TODO: find a better way
    btn->size = vec2(1, 1);
    btn->position = vec2(1, 1);
    btn->RGBA = vec4(1, 1, 1, 1);
    btn->opt = NO_OPT;
    btn->icon = nullptr;

    btnList.push_back(btn);
  }

  descriptionLine1 = "Bone!";
  descriptionLine1Pos = vec2(0, 0);
}

shared_ptr<TowerUiButtonComponent::TowerUiBtn> TowerUiButtonComponent::getCurrentSelectedBtn() {
  for (const shared_ptr<TowerUiButtonComponent::TowerUiBtn> btn : btnList)
    if (btn->relativeIndex == MIDDLE_TOWER_UI_BUTTON_RELATIVE_INDEX)
      return btn;
  return nullptr;
}

void TowerUiButtonComponent::setOptList(vector<TOWER_UI_OPT_TYPE> _optList) {
  if (_optList.size() != 0) this->optList = _optList;
}

TOWER_UI_OPT_TYPE TowerUiButtonComponent::getOptListAt(int index) {
  if (optList.size() == 0) return NO_OPT;
  return optList.at(wrapIndex(index, optList.size()));
}

void TowerUiButtonComponent::resetSelectedOptIndex() {
  currentSelectedOptIndex = 0;
  // currentSelectedBuildOptIndex will not be reset
}

void TowerUiButtonComponent::shiftLeftSelectedOptIndex() {
  if (isTowerHere)
    currentSelectedOptIndex = wrapIndex(currentSelectedOptIndex + 1, optList.size());
  else
    currentSelectedBuildOptIndex = wrapIndex(currentSelectedBuildOptIndex + 1, optList.size());
}

void TowerUiButtonComponent::shiftRightSelectedOptIndex() {
  if (isTowerHere)
    currentSelectedOptIndex = wrapIndex(currentSelectedOptIndex - 1, optList.size());
  else
    currentSelectedBuildOptIndex = wrapIndex(currentSelectedBuildOptIndex - 1, optList.size());
}

int TowerUiButtonComponent::getSelectedOptIndex() {
  if (isTowerHere)
    return currentSelectedOptIndex;
  else
    return currentSelectedBuildOptIndex;
}

int TowerUiButtonComponent::wrapIndex(int inputIndex, size_t totalLength) {
  int totalLength_int = (int)totalLength;
  return (inputIndex % totalLength_int + totalLength_int) % totalLength_int;
}
