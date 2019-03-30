#include "tower_ui_shift_right_state.hpp"

TowerUiShiftRightState::TowerUiShiftRightState() {
  duration = 0.0f;
  totalTime = SHIFT_RIGHT_TOTAL_TIME;
}

void TowerUiShiftRightState::input(EntityManager &entityManager, GLboolean keys[], GLboolean keysProcessed[]) {
  // curretly in the middle of shift right state, cannot change state
  return;
}

void TowerUiShiftRightState::update(EntityManager &entityManager, float dt) {
  // increase duration of current state
  duration += dt;

  vector<shared_ptr<Entity>> playerEntities =
      entityManager.getEntities(entityManager.getComponentChecker(vector<int>{ComponentType::player}));
  vector<shared_ptr<Entity>> towerUiEntities =
      entityManager.getEntities(entityManager.getComponentChecker(vector<int>{ComponentType::tower_ui_button, ComponentType::tower_ui_button_meta, ComponentType::tower_ui_state}));

  if (playerEntities.size() == 0 || towerUiEntities.size() == 0) return;

  shared_ptr<TowerUiButtonComponent> towerUiButton = towerUiEntities[0]->getComponent<TowerUiButtonComponent>();
  shared_ptr<TowerUiButtonMetaComponent> towerUiButtonMeta = towerUiEntities[0]->getComponent<TowerUiButtonMetaComponent>();
  shared_ptr<TransformComponent> playerTransformComponent = playerEntities[0]->getComponent<TransformComponent>();

  if (towerUiButton == nullptr || towerUiButtonMeta == nullptr || playerTransformComponent == nullptr) return;
  glm::vec2 playerCenterTopPosition = glm::vec2(playerTransformComponent->position.x + playerTransformComponent->size.x * 0.5, playerTransformComponent->position.y);

  towerUiButton->descriptionLine1 = "";
  towerUiButton->descriptionLine1Pos = towerUiButtonMeta->descriptionLine1Pos + playerCenterTopPosition;
  towerUiButton->descriptionLine2 = "";
  towerUiButton->descriptionLine2Pos = towerUiButtonMeta->descriptionLine1Pos + playerCenterTopPosition;
  towerUiButton->descriptionLine1Color = towerUiButton->defaultTextColor;

  // Update buttons position/size/color
  vector<shared_ptr<TowerUiButtonComponent::TowerUiBtn>> btnList = towerUiButton->btnList;
  for (shared_ptr<TowerUiButtonComponent::TowerUiBtn> btn : btnList) {
    if (btn == nullptr) continue;

    // Update buttons position/size/color
    switch (btn->relativeIndex) {
      case LEFT_TOWER_UI_BUTTON_RELATIVE_INDEX:   // left -> middle
        btn->position = playerCenterTopPosition + computeCatmullRomInterpolation(towerUiButtonMeta->rightButtonRelativePosition, towerUiButtonMeta->leftButtonRelativePosition, towerUiButtonMeta->middleButtonRelativePosition);
        btn->size = computeCatmullRomInterpolation(towerUiButtonMeta->rightButtonSize, towerUiButtonMeta->leftButtonSize, towerUiButtonMeta->middleButtonSize);
        btn->RGBA = computeLinearInterpolation(towerUiButtonMeta->leftButtonRGBA, towerUiButtonMeta->middleButtonRGBA);
        btn->opt = towerUiButton->getOptListAt(towerUiButton->getSelectedOptIndex() + btn->relativeIndex);
        btn->icon = towerUiButtonMeta->getTextureByOpt(btn->opt);
        break;
      case MIDDLE_TOWER_UI_BUTTON_RELATIVE_INDEX: // middle -> right
        btn->position = playerCenterTopPosition + computeCatmullRomInterpolation(towerUiButtonMeta->leftButtonRelativePosition, towerUiButtonMeta->middleButtonRelativePosition, towerUiButtonMeta->rightButtonRelativePosition);
        btn->size = computeCatmullRomInterpolation(towerUiButtonMeta->leftButtonSize, towerUiButtonMeta->middleButtonSize, towerUiButtonMeta->rightButtonSize);
        btn->RGBA = computeLinearInterpolation(towerUiButtonMeta->middleButtonRGBA, towerUiButtonMeta->rightButtonRGBA);
        btn->opt = towerUiButton->getOptListAt(towerUiButton->getSelectedOptIndex() + btn->relativeIndex);
        btn->icon = towerUiButtonMeta->getTextureByOpt(btn->opt);
        break;
      case RIGHT_TOWER_UI_BUTTON_RELATIVE_INDEX: // right -> left
        btn->position = playerCenterTopPosition + computeCatmullRomInterpolation(towerUiButtonMeta->middleButtonRelativePosition, towerUiButtonMeta->rightButtonRelativePosition, towerUiButtonMeta->leftButtonRelativePosition);
        btn->size = computeCatmullRomInterpolation(towerUiButtonMeta->middleButtonSize, towerUiButtonMeta->rightButtonSize, towerUiButtonMeta->leftButtonSize);
        btn->RGBA = computeLinearInterpolation(towerUiButtonMeta->rightButtonRGBA, towerUiButtonMeta->leftButtonRGBA);
        btn->opt = towerUiButton->getOptListAt(towerUiButton->getSelectedOptIndex() + btn->relativeIndex);
        btn->icon = towerUiButtonMeta->getTextureByOpt(btn->opt);
        break;
      default:
        break;
    }
  }

  // if touch the end of state
  // then finish current state and move to next state
  if (duration >= totalTime) {
    // update index
    towerUiButton->shiftRightSelectedOptIndex();

    // update relative index
    vector<shared_ptr<TowerUiButtonComponent::TowerUiBtn>> btnList = towerUiButton->btnList;
    for (shared_ptr<TowerUiButtonComponent::TowerUiBtn> btn : btnList) {
      if (btn == nullptr) continue;

      switch (btn->relativeIndex) {
        case RIGHT_TOWER_UI_BUTTON_RELATIVE_INDEX:   // right -> left
          btn->relativeIndex = LEFT_TOWER_UI_BUTTON_RELATIVE_INDEX;
          break;
        case MIDDLE_TOWER_UI_BUTTON_RELATIVE_INDEX: // middle -> right
          btn->relativeIndex = RIGHT_TOWER_UI_BUTTON_RELATIVE_INDEX;
          break;
        case LEFT_TOWER_UI_BUTTON_RELATIVE_INDEX: // left -> middle
          btn->relativeIndex = MIDDLE_TOWER_UI_BUTTON_RELATIVE_INDEX;
          break;
        default:
          break;
      }
    }

    // create a new state
    shared_ptr<TowerUiStateComponent> newState = make_shared<TowerUiIdleState>();
    // update state
    for (shared_ptr<Entity> e : towerUiEntities) {
      e->setComponent<TowerUiStateComponent>(newState);
    }
    // towerUiStateSystem pointer points to new instace, delete currect state
    // the deletion will be handled by smart pointer
  }
}

