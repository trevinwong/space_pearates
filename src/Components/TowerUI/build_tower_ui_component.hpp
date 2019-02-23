#ifndef BUILD_TOWER_UI_COMPONENT_H
#define BUILD_TOWER_UI_COMPONENT_H

#include "../../texture.hpp"
#include "../../utility.hpp"
#include "../base_component.hpp"

/*
  This component is used to store some meta data for Build Tower UI
  In short, our game have two sets of Build Tower UI
  if the player at a block and this block can be used to build tower,
  then:
    if a tower already exists there, then player can do [FIX, SELL, UPGRADE]  <= see OperateTowerUiComponent class
    if no tower exists there, then player can build [TOWER#1, TOWER#2, TOWER#3 ...] <= stored this class
*/
class BuildTowerUiComponent : public BaseComponent {
  public:
    BuildTowerUiComponent();

    // Build Tower UI for tower building
    int getCurrentSelectedTowerTypeListIndex();
    void moveLeftCurrentSelectedTowerTypeListIndex();
    void moveRightCurrentSelectedTowerTypeListIndex();
    BUILD_TOWER_UI_BUTTON_TYPE getTowerTypeListAt(int index);
    Texture* getTowerTypeListUiIconsAt(int index);

    static const int typeID = ComponentType::build_tower_ui;
    inline virtual int getTypeID() const { return typeID; };

  private:

    int currentSelectedTowerTypeListIndex;
    vector<BUILD_TOWER_UI_BUTTON_TYPE> towerTypeList;  // this list is used for logic
    vector<Texture*> towerTypeListUiIcons;  // this list is used for render

    // use this function to avoid out of boundary index
    // e.g. size = 3
    // then foreach index i = [-1 ... 6]:
    // i      =-3  -2  -1  0  1  2  3  4  5  6
    // result = 0   1   2  0  1  2  0  1  2  0
    int wrapIndex(int inputIndex, size_t totalLength);
};

#endif // !BUILD_TOWER_UI_COMPONENT_H
