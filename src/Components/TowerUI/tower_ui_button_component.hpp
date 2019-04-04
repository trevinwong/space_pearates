#ifndef TOWER_UI_BUTTON_COMPONENT_H
#define TOWER_UI_BUTTON_COMPONENT_H

#include "../../Utility/utility.hpp"
#include "../base_component.hpp"
#include "../sprite_component.hpp"

#define TOWER_UI_BUTTON_NUMBER 3

namespace TowerUiStateType {
  enum TowerUiStateType {
    Idle,
    ShiftLeft,
    ShiftRight
  };
}

class TowerUiButtonComponent : public BaseComponent {
public:
  TowerUiButtonComponent();

  bool isDisplay;

  vec2 tilePosition;
  bool isTowerHere;

  struct TowerUiBtn{
    int relativeIndex;
    glm::vec2 size;
    glm::vec2 position;
    glm::vec4 RGBA;
    TOWER_UI_OPT_TYPE opt;
    shared_ptr<Texture> icon;
  };
  vector<shared_ptr<TowerUiBtn>> btnList;

  // line 1 is below line2
  string descriptionLine2;
  string descriptionLine1;
  // descriptionLine1 pos
  glm::vec2 descriptionLine2Pos;
  glm::vec2 descriptionLine1Pos;

  vec3 defaultTextColor = vec3(1.f, 1.f, 0.f);
  vec3 noMoneyTextColor = vec3(1.f, 0.f, 0.f);
  vec3 descriptionLine1Color = defaultTextColor;

  

  shared_ptr<TowerUiBtn> getCurrentSelectedBtn();

  int getSelectedOptIndex();
  void resetSelectedOptIndex();
  void shiftLeftSelectedOptIndex();
  void shiftRightSelectedOptIndex();

  void setOptList(vector<TOWER_UI_OPT_TYPE> optList);
  TOWER_UI_OPT_TYPE getOptListAt(int index);

  static const int typeID = ComponentType::tower_ui_button;
  inline virtual int getTypeID() const { return typeID; };

private:
  int currentSelectedOptIndex;
  vector<TOWER_UI_OPT_TYPE> optList;

  // use this function to avoid out of boundary index
  // e.g. size = 3
  // then foreach index i = [-1 ... 6]:
  // i      =-3  -2  -1  0  1  2  3  4  5  6
  // result = 0   1   2  0  1  2  0  1  2  0
  int wrapIndex(int inputIndex, size_t totalLength);
};

#endif // !TOWER_UI_BUTTON_COMPONENT_H
