#ifndef TOWER_UI_BUTTON_META_H
#define TOWER_UI_BUTTON_META_H

#include "../../utility.hpp"
#include "../base_component.hpp"

#define LEFT_TOWER_UI_BUTTON_RELATIVE_INDEX -1 
#define MIDDLE_TOWER_UI_BUTTON_RELATIVE_INDEX 0 
#define RIGHT_TOWER_UI_BUTTON_RELATIVE_INDEX 1

#define BUILD_TOWER_UI_BUTTON_SIZE_DIFF 8.0f
#define BUILD_TOWER_UI_BUTTON_DISTANCE 20.0f

/*
  This component is used to store the key frames for animation
*/

class TowerUiButtonMetaComponent : public BaseComponent {
  public:
    TowerUiButtonMetaComponent();

    // These variables are init in the constructor
    // These variables will not be changed during runtime, they are used as keyframes to compute animation path
    glm::vec2 leftButtonSize;
    glm::vec2 middleButtonSize;
    glm::vec2 rightButtonSize;

    glm::vec2 leftButtonRelativePosition;
    glm::vec2 middleButtonRelativePosition;
    glm::vec2 rightButtonRelativePosition;

    glm::vec4 leftButtonRGBA;
    glm::vec4 middleButtonRGBA;
    glm::vec4 rightButtonRGBA;

    static const int typeID = ComponentType::tower_ui_button_meta;
    inline virtual int getTypeID() const { return typeID; };

};

#endif // !TOWER_UI_BUTTON_COMPONENT_META_H
