#ifndef TOWER_UI_BUTTON_META_H
#define TOWER_UI_BUTTON_META_H

#include <texture.hpp>
#include <program.hpp>
#include <text.hpp>
#include <utility.hpp>
#include "../base_component.hpp"

#define BUILD_TOWER_UI_BUTTON_SIZE_DIFF 8.0f
#define BUILD_TOWER_UI_BUTTON_DISTANCE 20.0f

class TowerUiButtonMetaComponent : public BaseComponent {
public:
  TowerUiButtonMetaComponent();

  shared_ptr<Program> program;
  GLuint  quadVAO;

  // These variables are init in the constructor
  // These variables will not be changed during runtime, they are used as keyframes to compute animation path
  vec2 leftButtonSize;
  vec2 middleButtonSize;
  vec2 rightButtonSize;

  vec2 leftButtonRelativePosition;
  vec2 middleButtonRelativePosition;
  vec2 rightButtonRelativePosition;

  glm::vec4 leftButtonRGBA;
  glm::vec4 middleButtonRGBA;
  glm::vec4 rightButtonRGBA;

  // descriptionLine1 pos
  vec2 descriptionLine1Pos;
  // descriptionLine2 pos
  vec2 descriptionLine2Pos;

  // icons
  shared_ptr<Texture> buildFireTowerIcon;
  shared_ptr<Texture> buildWaterTowerIcon;
  shared_ptr<Texture> buildLightTowerIcon;
  shared_ptr<Texture> buildStarTowerIcon;
  shared_ptr<Texture> buildBoomerangTowerIcon;
  shared_ptr<Texture> fixTowerIcon;
  shared_ptr<Texture> sellTowerIcon;
  shared_ptr<Texture> upgradeTowerIcon;

  shared_ptr<Texture> getTextureByOpt(TOWER_UI_OPT_TYPE opt);
  vector<TOWER_UI_OPT_TYPE> buildOptList;
  vector<TOWER_UI_OPT_TYPE> towerOptList;

  static const int typeID = ComponentType::tower_ui_button_meta;
  inline virtual int getTypeID() const { return typeID; };

private:
  void initProgramAndShader();
  void initIcons();
  void initKeyframePos();
};

#endif // !TOWER_UI_BUTTON_META_H
