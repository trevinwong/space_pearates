#ifndef TOWER_UI_BUTTON_COMPONENT_H
#define TOWER_UI_BUTTON_COMPONENT_H

#include "../../utility.hpp"
#include "../base_component.hpp"
#include "../sprite_component.hpp"

/*
  Each tower ui button has one of this component
  contains size, position and RGBA
*/
class TowerUiButtonComponent : public SpriteComponent {
  public:
    TowerUiButtonComponent(int _relativeIndex, Program *_program, Texture *_texture);

    // those values will be updated during run time
    int relativeIndex;
    glm::vec2 size;
    glm::vec2 position;
    glm::vec4 RGBA;
    // TODO: add rotate

    static const int typeID = ComponentType::tower_ui_button;
    inline virtual int getTypeID() const { return typeID; };
  private:
};

#endif // !TOWER_UI_BUTTON_COMPONENT_H
