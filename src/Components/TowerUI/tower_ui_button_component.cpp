#include "tower_ui_button_component.hpp"

TowerUiButtonComponent::TowerUiButtonComponent(int _relativeIndex, Program *_program, Texture *_texture):
  SpriteComponent(_program, _texture),
  relativeIndex(_relativeIndex)
{
  size = glm::vec2(1, 1);       // default init value
  position = glm::vec2(0, 0);   // default init value
  RGBA = glm::vec4(1, 1, 1, 1); // default init value
}
