#ifndef OPERATE_TOWER_UI_COMPONENT_H
#define OPERATE_TOWER_UI_COMPONENT_H

#include "../../texture.hpp"
#include "../../utility.hpp"
#include "../base_component.hpp"

/*
  [FIX, UPGRADE, SELL] operations
*/

class OperateTowerUiComponent : public BaseComponent {
public:
  OperateTowerUiComponent();
    
    // Operate Tower UI
  int getCurrentSelectedTowerOperationListIndex();
  void moveLeftCurrentSelectedTowerOperationListIndex();
  void moveRightCurrentSelectedTowerOperationListIndex();
  BUILD_TOWER_UI_BUTTON_TYPE getTowerOperationListAt(int index);
  Texture* getTowerOperationListUiIconsAt(int index);

  static const int typeID = ComponentType::operate_tower_ui;
  inline virtual int getTypeID() const { return typeID; };

private:

  int currentSelectedTowerOperationListIndex;
  vector<BUILD_TOWER_UI_BUTTON_TYPE> towerOperationList; // this list is used for logic
  vector<Texture*> towerOperationListUiIcons; // this list is used for render

  // use this function to avoid out of boundary index
  // e.g. size = 3
  // then foreach index i = [-1 ... 6]:
  // i      =-3  -2  -1  0  1  2  3  4  5  6
  // result = 0   1   2  0  1  2  0  1  2  0
  int wrapIndex(int inputIndex, size_t totalLength);
};

#endif // !OPERATE_TOWER_UI_COMPONENT_H
