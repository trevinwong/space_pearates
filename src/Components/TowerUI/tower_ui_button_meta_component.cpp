#include "tower_ui_button_meta_component.hpp"

TowerUiButtonMetaComponent::TowerUiButtonMetaComponent() {
  initProgramAndShader();
  initIcons();
  initKeyframePos();

  buildOptList.push_back(BUILD_FIRE_TOWER);
  buildOptList.push_back(BUILD_WATER_TOWER);
  buildOptList.push_back(BUILD_LIGHT_TOWER);
  buildOptList.push_back(BUILD_STAR_TOWER);
  buildOptList.push_back(BUILD_BOOMERANG_TOWER);

  towerOptList.push_back(FIX_TOWER_OPERATION);
  towerOptList.push_back(UPGRADE_TOWER_OPERATION);
  towerOptList.push_back(SELL_TOWER_OPERATION);
}

TowerUiButtonMetaComponent::~TowerUiButtonMetaComponent() {
  glDeleteBuffers(1, &this->VBO);
  glDeleteVertexArrays(1, &this->quadVAO);
}

void TowerUiButtonMetaComponent::initProgramAndShader() {
  program = make_shared<Program>(shader_path("sprite.vert"), shader_path("sprite.frag"));

  GLfloat vertices[] = {
      // Pos      // Tex
      0.0f, 1.0f, 0.0f, 1.0f,
      1.0f, 0.0f, 1.0f, 0.0f,
      0.0f, 0.0f, 0.0f, 0.0f,

      0.0f, 1.0f, 0.0f, 1.0f,
      1.0f, 1.0f, 1.0f, 1.0f,
      1.0f, 0.0f, 1.0f, 0.0f
  };

  // Generate a VAO.
  glGenVertexArrays(1, &this->quadVAO);
  // Generate a VBO.
  glGenBuffers(1, &VBO);

  // Bind our current VBO.
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // Move the vertices we defined above into our VBO.
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  // Bind our current VAO, which will remember any vertex attribute related calls.
  glBindVertexArray(this->quadVAO);
  // Enable the first "in" variable in our vertex shader - make sure that this corresponds to the right variable!
  // i.e. layout (location = 0) in shaders
  glEnableVertexAttribArray(0);
  //                   (index, size, type, isNormalized, stride, pointer to offset)
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid *) 0);
  // layout (location = 1)
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid *) (2 * sizeof(GLfloat)));

  // Re-bind the current VBO and VAO to 0 to avoid accidentally modifying the ones we just configured here.
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void TowerUiButtonMetaComponent::initIcons() {
  buildFireTowerIcon = make_shared<Texture>(texture_path("build_fire_tower_icon.png"), true);
  buildWaterTowerIcon = make_shared<Texture>(texture_path("build_water_tower_icon.png"), true);
  buildLightTowerIcon = make_shared<Texture>(texture_path("build_light_tower_icon.png"), true);
  buildStarTowerIcon = make_shared<Texture>(texture_path("build_star_tower_icon.png"), true);
  buildBoomerangTowerIcon = make_shared<Texture>(texture_path("build_boomerang_tower_icon.png"), true);

  fixTowerIcon = make_shared<Texture>(texture_path("fix_tower_icon.png"), true);
  sellTowerIcon = make_shared<Texture>(texture_path("sell_tower_icon.png"), true);
  upgradeTowerIcon = make_shared<Texture>(texture_path("upgrade_tower_icon.png"), true);
}

void TowerUiButtonMetaComponent::initKeyframePos() {
  middleButtonSize = glm::vec2(50, 50);

  // UI layer
  // left button
  leftButtonSize = middleButtonSize - BUILD_TOWER_UI_BUTTON_SIZE_DIFF * glm::abs((float) LEFT_TOWER_UI_BUTTON_RELATIVE_INDEX);
  leftButtonRelativePosition = glm::vec2(0, -50) + (float) LEFT_TOWER_UI_BUTTON_RELATIVE_INDEX * glm::vec2(BUILD_TOWER_UI_BUTTON_DISTANCE, 0) - leftButtonSize * 0.5f;

  // middle button
  middleButtonSize = middleButtonSize - BUILD_TOWER_UI_BUTTON_SIZE_DIFF * glm::abs((float) MIDDLE_TOWER_UI_BUTTON_RELATIVE_INDEX);
  middleButtonRelativePosition = glm::vec2(0, -50) + (float) MIDDLE_TOWER_UI_BUTTON_RELATIVE_INDEX * glm::vec2(BUILD_TOWER_UI_BUTTON_DISTANCE, 0) - middleButtonSize * 0.5f;

  // right button
  rightButtonSize = middleButtonSize - BUILD_TOWER_UI_BUTTON_SIZE_DIFF * glm::abs((float) RIGHT_TOWER_UI_BUTTON_RELATIVE_INDEX);
  rightButtonRelativePosition = glm::vec2(0, -50) + (float) RIGHT_TOWER_UI_BUTTON_RELATIVE_INDEX * glm::vec2(BUILD_TOWER_UI_BUTTON_DISTANCE, 0) - rightButtonSize * 0.5f;

  leftButtonRGBA = glm::vec4(1.0, 1.0, 1.0, 0.5);
  middleButtonRGBA = glm::vec4(1.0, 1.0, 1.0, 1.0);
  rightButtonRGBA = glm::vec4(1.0, 1.0, 1.0, 0.5);

  // Note: line1 is below line2
  descriptionLine1Pos = vec2(middleButtonRelativePosition.x, middleButtonRelativePosition.y - 6);
  descriptionLine2Pos = vec2(middleButtonRelativePosition.x, middleButtonRelativePosition.y - 22);
}

shared_ptr<Texture> TowerUiButtonMetaComponent::getTextureByOpt(TOWER_UI_OPT_TYPE opt) {
  switch (opt) {
    case BUILD_FIRE_TOWER:
      return buildFireTowerIcon;
    case BUILD_WATER_TOWER:
      return buildWaterTowerIcon;
    case BUILD_LIGHT_TOWER:
      return buildLightTowerIcon;
    case BUILD_STAR_TOWER:
      return buildStarTowerIcon;
    case BUILD_BOOMERANG_TOWER:
      return buildBoomerangTowerIcon;
    case SELL_TOWER_OPERATION:
      return sellTowerIcon;
    case UPGRADE_TOWER_OPERATION:
      return upgradeTowerIcon;
    case FIX_TOWER_OPERATION:
      return fixTowerIcon;
    case NO_OPT:
    default:
      break;
  }
}
