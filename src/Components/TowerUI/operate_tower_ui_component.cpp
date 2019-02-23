#include "operate_tower_ui_component.hpp"

OperateTowerUiComponent::OperateTowerUiComponent()
{
  // UI for tower already existed at some pos
  currentSelectedTowerOperationListIndex = 0;

  towerOperationList.push_back(SELL_TOWER_OPERATION);
  towerOperationList.push_back(UPGRADE_TOWER_OPERATION);
  towerOperationList.push_back(FIX_TOWER_OPERATION);

  // Sell Tower Sprite
  Texture *sellTowerSpriteTexture = new Texture(texture_path("sell_tower_icon.png"), true);
  // Upgrade Tower Sprite
  Texture *upgradeTowerSpriteTexture = new Texture(texture_path("upgrade_tower_icon.png"), true);
  // Fix Tower Sprite
  Texture *fixTowerSpriteTexture = new Texture(texture_path("fix_tower_icon.png"), true);

  towerOperationListUiIcons.push_back(sellTowerSpriteTexture);
  towerOperationListUiIcons.push_back(upgradeTowerSpriteTexture);
  towerOperationListUiIcons.push_back(fixTowerSpriteTexture);
}

int OperateTowerUiComponent::getCurrentSelectedTowerOperationListIndex()
{
  return currentSelectedTowerOperationListIndex;
}

void OperateTowerUiComponent::moveLeftCurrentSelectedTowerOperationListIndex()
{
  currentSelectedTowerOperationListIndex = 
    wrapIndex(currentSelectedTowerOperationListIndex - 1, towerOperationList.size());
}

void OperateTowerUiComponent::moveRightCurrentSelectedTowerOperationListIndex()
{
  currentSelectedTowerOperationListIndex = 
    wrapIndex(currentSelectedTowerOperationListIndex + 1, towerOperationList.size());
}

BUILD_TOWER_UI_BUTTON_TYPE OperateTowerUiComponent::getTowerOperationListAt(int index)
{
  return towerOperationList[wrapIndex(index, towerOperationList.size())];
}

Texture * OperateTowerUiComponent::getTowerOperationListUiIconsAt(int index)
{
  return towerOperationListUiIcons[wrapIndex(index, towerOperationListUiIcons.size())];
}

int OperateTowerUiComponent::wrapIndex(int inputIndex, size_t totalLength)
{
  int totalLength_int = (int)totalLength;
  return (inputIndex % totalLength_int + totalLength_int) % totalLength_int;
}