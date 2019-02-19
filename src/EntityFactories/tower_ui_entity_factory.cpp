#include "tower_ui_entity_factory.hpp"

vector<Entity> TowerUiEntityFactory::createTowerUiButtons()
{
  vector<Entity> towerUiButtonEntites;

  // those component are shared btw ui buttons
  BuildTowerUiComponent *towerUiComponent = new BuildTowerUiComponent();
  OperateTowerUiComponent *operateTowerUiComponent = new OperateTowerUiComponent();
  TowerUiButtonMetaComponent *towerUiButtonMetaComponent = new TowerUiButtonMetaComponent();
  TowerUiStateComponent *idleState = new TowerUiIdleState();

  // left button
  Entity leftButton;
  Program *leftButtonProgram = new Program(shader_path("sprite.vert"), shader_path("sprite.frag"));
  Texture *leftButtonTexture = operateTowerUiComponent->getTowerOperationListUiIconsAt(0);  // get one as a place holder, will changed during runtime
  TowerUiButtonComponent *leftButton_towerUiButtonComponent = 
    new TowerUiButtonComponent(LEFT_TOWER_UI_BUTTON_RELATIVE_INDEX, leftButtonProgram, leftButtonTexture);
  leftButton.setComponent<TowerUiButtonComponent>(leftButton_towerUiButtonComponent);
  leftButton.setComponent<BuildTowerUiComponent>(towerUiComponent);
  leftButton.setComponent<OperateTowerUiComponent>(operateTowerUiComponent);
  leftButton.setComponent<TowerUiButtonMetaComponent>(towerUiButtonMetaComponent);
  leftButton.setComponent<TowerUiStateComponent>(idleState);

  // middle button
  Entity middleButton;
  Program *middleButtonProgram = new Program(shader_path("sprite.vert"), shader_path("sprite.frag"));
  Texture *middleButtonTexture = operateTowerUiComponent->getTowerOperationListUiIconsAt(0);  // get one as a place holder, will changed during runtime
  TowerUiButtonComponent *middleButton_towerUiButtonComponent =
    new TowerUiButtonComponent(MIDDLE_TOWER_UI_BUTTON_RELATIVE_INDEX, middleButtonProgram, middleButtonTexture);
  middleButton.setComponent<TowerUiButtonComponent>(middleButton_towerUiButtonComponent);
  middleButton.setComponent<BuildTowerUiComponent>(towerUiComponent);
  middleButton.setComponent<OperateTowerUiComponent>(operateTowerUiComponent);
  middleButton.setComponent<TowerUiButtonMetaComponent>(towerUiButtonMetaComponent);
  middleButton.setComponent<TowerUiStateComponent>(idleState);

  // right button
  Entity rightButton;
  Program *rightButtonProgram = new Program(shader_path("sprite.vert"), shader_path("sprite.frag"));
  Texture *rightButtonTexture = operateTowerUiComponent->getTowerOperationListUiIconsAt(0);  // get one as a place holder, will changed during runtime
  TowerUiButtonComponent *rightButton_towerUiButtonComponent =
    new TowerUiButtonComponent(RIGHT_TOWER_UI_BUTTON_RELATIVE_INDEX, rightButtonProgram, rightButtonTexture);
  rightButton.setComponent<TowerUiButtonComponent>(rightButton_towerUiButtonComponent);
  rightButton.setComponent<BuildTowerUiComponent>(towerUiComponent);
  rightButton.setComponent<OperateTowerUiComponent>(operateTowerUiComponent);
  rightButton.setComponent<TowerUiButtonMetaComponent>(towerUiButtonMetaComponent);
  rightButton.setComponent<TowerUiStateComponent>(idleState);

  towerUiButtonEntites.push_back(leftButton);
  towerUiButtonEntites.push_back(middleButton);
  towerUiButtonEntites.push_back(rightButton);

  return towerUiButtonEntites;
}
