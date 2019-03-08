#include "build_tower_ui_component.hpp"

BuildTowerUiComponent::BuildTowerUiComponent()
{
  // UI for tower not existed yet
  currentSelectedTowerTypeListIndex = 0;

  towerTypeList.push_back(BUILD_FIRE_TOWER);
  towerTypeList.push_back(BUILD_WATER_TOWER);
  towerTypeList.push_back(BUILD_LIGHT_TOWER);
  towerTypeList.push_back(BUILD_STAR_TOWER);

  // Fire Tower Sprite
  Texture *fireTowerSpriteTexture = new Texture(texture_path("build_fire_tower_icon.png"), true);
  // Water Tower Sprite
  Texture *waterTowerSpriteTexture = new Texture(texture_path("build_water_tower_icon.png"), true);
  // Light Tower Sprite
  Texture *lightTowerSpriteTexture = new Texture(texture_path("build_light_tower_icon.png"), true);
  // Star Tower Sprite
  Texture *starTowerSpriteTexture = new Texture(texture_path("build_star_tower_icon.png"), true);
  
  towerTypeListUiIcons.push_back(fireTowerSpriteTexture);
  towerTypeListUiIcons.push_back(waterTowerSpriteTexture);
  towerTypeListUiIcons.push_back(lightTowerSpriteTexture);
  towerTypeListUiIcons.push_back(starTowerSpriteTexture);
}

int BuildTowerUiComponent::getCurrentSelectedTowerTypeListIndex()
{
  return currentSelectedTowerTypeListIndex;
}

void BuildTowerUiComponent::moveLeftCurrentSelectedTowerTypeListIndex()
{
  currentSelectedTowerTypeListIndex = wrapIndex(currentSelectedTowerTypeListIndex - 1, towerTypeList.size());
}

void BuildTowerUiComponent::moveRightCurrentSelectedTowerTypeListIndex()
{
  currentSelectedTowerTypeListIndex = wrapIndex(currentSelectedTowerTypeListIndex + 1, towerTypeList.size());
}

BUILD_TOWER_UI_BUTTON_TYPE BuildTowerUiComponent::getTowerTypeListAt(int index)
{
  return towerTypeList[wrapIndex(index, towerTypeList.size())];
}

Texture * BuildTowerUiComponent::getTowerTypeListUiIconsAt(int index)
{
  return towerTypeListUiIcons[wrapIndex(index, towerTypeListUiIcons.size())];
}


int BuildTowerUiComponent::wrapIndex(int inputIndex, size_t totalLength)
{
  int totalLength_int = (int)totalLength;
  return (inputIndex % totalLength_int + totalLength_int) % totalLength_int;
}
