#include "tower_ui_button_meta_component.hpp"

TowerUiButtonMetaComponent::TowerUiButtonMetaComponent()
{
  middleButtonSize = glm::vec2(50, 50);

  // UI layer 
  // left button
  leftButtonSize = middleButtonSize - BUILD_TOWER_UI_BUTTON_SIZE_DIFF * glm::abs((float)LEFT_TOWER_UI_BUTTON_RELATIVE_INDEX);
  leftButtonRelativePosition = glm::vec2(0, -50) + (float)LEFT_TOWER_UI_BUTTON_RELATIVE_INDEX * glm::vec2(BUILD_TOWER_UI_BUTTON_DISTANCE, 0) - leftButtonSize * 0.5f;

  // middle button
  middleButtonSize = middleButtonSize - BUILD_TOWER_UI_BUTTON_SIZE_DIFF * glm::abs((float)MIDDLE_TOWER_UI_BUTTON_RELATIVE_INDEX);
  middleButtonRelativePosition = glm::vec2(0, -50) + (float)MIDDLE_TOWER_UI_BUTTON_RELATIVE_INDEX * glm::vec2(BUILD_TOWER_UI_BUTTON_DISTANCE, 0) - middleButtonSize * 0.5f;

  // right button
  rightButtonSize = middleButtonSize - BUILD_TOWER_UI_BUTTON_SIZE_DIFF * glm::abs((float)RIGHT_TOWER_UI_BUTTON_RELATIVE_INDEX);
  rightButtonRelativePosition = glm::vec2(0, -50) + (float)RIGHT_TOWER_UI_BUTTON_RELATIVE_INDEX * glm::vec2(BUILD_TOWER_UI_BUTTON_DISTANCE, 0) - rightButtonSize * 0.5f;

  leftButtonRGBA = glm::vec4(1.0, 1.0, 1.0, 0.5);
  middleButtonRGBA = glm::vec4(1.0, 1.0, 1.0, 1.0);
  rightButtonRGBA = glm::vec4(1.0, 1.0, 1.0, 0.5);
}
