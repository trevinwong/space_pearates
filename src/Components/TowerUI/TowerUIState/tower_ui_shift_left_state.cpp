#include "tower_ui_shift_left_state.hpp"

TowerUiShiftLeftState::TowerUiShiftLeftState()
{
  duration = 0.0f;
  totalTime = SHIFT_LEFT_TOTAL_TIME;
}

void TowerUiShiftLeftState::input(EntityManager &entityManager, GLboolean keys[], GLboolean keysProcessed[]) {
  // curretly in the middle of shift left state, cannot change state
  return;
}

void TowerUiShiftLeftState::update(EntityManager &entityManager, float dt) {
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

  // Update buttons position/size/color
  vector<shared_ptr<TowerUiButtonComponent::TowerUiBtn>> btnList = towerUiButton->btnList;
  for (shared_ptr<TowerUiButtonComponent::TowerUiBtn> btn : btnList) {
    if (btn == nullptr) continue;

    switch (btn->relativeIndex) {
      case LEFT_TOWER_UI_BUTTON_RELATIVE_INDEX:   // left -> right
        btn->position = playerCenterTopPosition + computeCatmullRomInterpolation(towerUiButtonMeta->middleButtonRelativePosition, towerUiButtonMeta->leftButtonRelativePosition, towerUiButtonMeta->rightButtonRelativePosition);
        btn->size = computeCatmullRomInterpolation(towerUiButtonMeta->middleButtonSize, towerUiButtonMeta->leftButtonSize, towerUiButtonMeta->rightButtonSize);
        btn->RGBA = computeLinearInterpolation(towerUiButtonMeta->leftButtonRGBA, towerUiButtonMeta->rightButtonRGBA);
        btn->opt = towerUiButton->getOptListAt(towerUiButton->getSelectedOptIndex() + btn->relativeIndex);
        btn->icon = towerUiButtonMeta->getTextureByOpt(btn->opt);
        break;
      case MIDDLE_TOWER_UI_BUTTON_RELATIVE_INDEX: // middle -> left
        btn->position = playerCenterTopPosition + computeCatmullRomInterpolation(towerUiButtonMeta->rightButtonRelativePosition, towerUiButtonMeta->middleButtonRelativePosition, towerUiButtonMeta->leftButtonRelativePosition);
        btn->size = computeCatmullRomInterpolation(towerUiButtonMeta->rightButtonSize, towerUiButtonMeta->middleButtonSize, towerUiButtonMeta->leftButtonSize);
        btn->RGBA = computeLinearInterpolation(towerUiButtonMeta->middleButtonRGBA, towerUiButtonMeta->leftButtonRGBA);
        btn->opt = towerUiButton->getOptListAt(towerUiButton->getSelectedOptIndex() + btn->relativeIndex);
        btn->icon = towerUiButtonMeta->getTextureByOpt(btn->opt);
        break;
      case RIGHT_TOWER_UI_BUTTON_RELATIVE_INDEX: // right -> middle
        btn->position = playerCenterTopPosition + computeCatmullRomInterpolation(towerUiButtonMeta->leftButtonRelativePosition, towerUiButtonMeta->rightButtonRelativePosition, towerUiButtonMeta->middleButtonRelativePosition);
        btn->size = computeCatmullRomInterpolation(towerUiButtonMeta->leftButtonSize, towerUiButtonMeta->rightButtonSize, towerUiButtonMeta->middleButtonSize);
        btn->RGBA = computeLinearInterpolation(towerUiButtonMeta->rightButtonRGBA, towerUiButtonMeta->middleButtonRGBA);
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
    towerUiButton->shiftLeftSelectedOptIndex();

    // update relative index
    vector<shared_ptr<TowerUiButtonComponent::TowerUiBtn>> btnList = towerUiButton->btnList;
    for (shared_ptr<TowerUiButtonComponent::TowerUiBtn> btn : btnList) {
      if (btn == nullptr) continue;

      switch (btn->relativeIndex) {
        case LEFT_TOWER_UI_BUTTON_RELATIVE_INDEX:   // left -> right
          btn->relativeIndex = RIGHT_TOWER_UI_BUTTON_RELATIVE_INDEX;
          break;
        case MIDDLE_TOWER_UI_BUTTON_RELATIVE_INDEX: // middle -> left
          btn->relativeIndex = LEFT_TOWER_UI_BUTTON_RELATIVE_INDEX;
          break;
        case RIGHT_TOWER_UI_BUTTON_RELATIVE_INDEX: // right -> middle
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
    // new state created and pointed, delete currect state
    // the deletion will be handled by smart pointer
  }
}
