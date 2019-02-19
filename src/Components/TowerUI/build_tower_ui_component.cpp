#include "build_tower_ui_component.hpp"

BuildTowerUiComponent::BuildTowerUiComponent()
{
  // UI for tower not existed yet
  this->currentSelectedTowerTypeListIndex = 0;

  this->towerTypeList.push_back(BUILD_FIRE_TOWER);
  this->towerTypeList.push_back(BUILD_LIGHT_TOWER);

  // Fire Tower Sprite
  Texture *fireTowerSpriteTexture = new Texture(texture_path("build_fire_tower_icon.png"), true);
  // Light Tower Sprite
  Texture *lightTowerSpriteTexture = new Texture(texture_path("build_light_tower_icon.png"), true);
  
  this->towerTypeListUiIcons.push_back(fireTowerSpriteTexture);
  this->towerTypeListUiIcons.push_back(lightTowerSpriteTexture);
}

BuildTowerUiComponent::~BuildTowerUiComponent()
{
}

int BuildTowerUiComponent::getCurrentSelectedTowerTypeListIndex()
{
  return this->currentSelectedTowerTypeListIndex;
}

void BuildTowerUiComponent::moveLeftCurrentSelectedTowerTypeListIndex()
{
  this->currentSelectedTowerTypeListIndex = this->wrapIndex(this->currentSelectedTowerTypeListIndex - 1, this->towerTypeList.size());
}

void BuildTowerUiComponent::moveRightCurrentSelectedTowerTypeListIndex()
{
  this->currentSelectedTowerTypeListIndex = this->wrapIndex(this->currentSelectedTowerTypeListIndex + 1, this->towerTypeList.size());
}

BUILD_TOWER_UI_BUTTON_TYPE BuildTowerUiComponent::getTowerTypeListAt(int index)
{
  return towerTypeList[this->wrapIndex(index, towerTypeList.size())];
}

Texture * BuildTowerUiComponent::getTowerTypeListUiIconsAt(int index)
{
  return towerTypeListUiIcons[this->wrapIndex(index, towerTypeListUiIcons.size())];
}


int BuildTowerUiComponent::wrapIndex(int inputIndex, size_t totalLength)
{
  int totalLength_int = (int)totalLength;
  return (inputIndex % totalLength_int + totalLength_int) % totalLength_int;
}
